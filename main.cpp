#include "mainwindow.h"

#include <QApplication>
#include <LayerShellQt/Window>
#include "resizehandle.h"
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

    layerWindow->setExclusiveZone(-1);
    w.resize(0,0);

    w.show();

    auto setupHandle = [](ResizeHandle* handle){
        handle -> show();
        handle -> windowHandle() -> close();

        auto lw = LayerShellQt::Window::get(handle->windowHandle());
        if(lw){
            lw->setLayer(LayerShellQt::Window::LayerOverlay);
        }
        else{
            qDebug() << "LayerShellQt failed for handle";
        }
    };

      return QApplication::exec();
}
