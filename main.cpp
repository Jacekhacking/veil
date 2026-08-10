#include "mainwindow.h"

#include <QApplication>
#include <LayerShellQt/Window>
#include <QWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.initLayerShell();

    auto layerWindow = LayerShellQt::Window::get(w.windowHandle());
    if(layerWindow){
    layerWindow->setLayer(LayerShellQt::Window::LayerOverlay);

    layerWindow->setAnchors(LayerShellQt::Window::Anchors(
        LayerShellQt::Window::AnchorLeft |
        LayerShellQt::Window::AnchorRight |
        LayerShellQt::Window::AnchorTop |
        LayerShellQt::Window::AnchorBottom
        ));
    }

    w.show();
    return QApplication::exec();
}
