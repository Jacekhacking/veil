#include "handlelayer.h"
#include "mainwindow.h"

#include <QApplication>
#include <QScreen>
#include <LayerShellQt/Window>

namespace {

/*
 * Pin a widget to the whole screen as a wlr-layer-shell surface on the overlay
 * layer. Anchoring all four edges with no exclusive zone of our own (-1 also
 * means "ignore other people's exclusive zones") is what keeps it above normal
 * windows and above panels, and KeyboardInteractivityNone keeps it from ever
 * stealing focus.
 */
bool makeOverlaySurface(QWindow *window, const QString &scope)
{
    auto *layer = LayerShellQt::Window::get(window);
    if (!layer) {
        qWarning() << "LayerShellQt failed for" << scope
                   << "- is this a wlr-layer-shell compositor?";
        return false;
    }

    layer->setScope(scope);
    layer->setLayer(LayerShellQt::Window::LayerOverlay);
    layer->setAnchors(LayerShellQt::Window::Anchors(
        LayerShellQt::Window::AnchorTop | LayerShellQt::Window::AnchorBottom |
        LayerShellQt::Window::AnchorLeft | LayerShellQt::Window::AnchorRight));
    layer->setExclusiveZone(-1);
    layer->setKeyboardInteractivity(LayerShellQt::Window::KeyboardInteractivityNone);
    layer->setActivateOnShow(false);
    return true;
}

}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow veil;
    HandleLayer handles;

    veil.initLayerShell();
    handles.initLayerShell();

    if (!makeOverlaySurface(veil.windowHandle(), QStringLiteral("veil")))
        return 1;
    if (!makeOverlaySurface(handles.windowHandle(), QStringLiteral("veil-handles")))
        return 1;

    QObject::connect(&handles, &HandleLayer::cornerMoved,
                     &veil, &MainWindow::onCornerMoved);
    QObject::connect(&veil, &MainWindow::veilRectChanged,
                     &handles, &HandleLayer::setRect);

    // Both surfaces cover the screen, so surface-local coordinates are screen
    // coordinates and the two stay in lockstep without any translation.
    const QSize screen = QGuiApplication::primaryScreen()->geometry().size();
    QRect start(QPoint(), screen * 3 / 5);
    start.moveCenter(QRect(QPoint(), screen).center());
    veil.setVeilRect(start);

    // Tint first so the grips end up above it in the overlay layer.
    veil.show();
    handles.show();

    return QApplication::exec();
}
