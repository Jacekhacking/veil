#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "resizehandle.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    void initLayerShell(){create();}


protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    Ui::MainWindow *ui;
    QPoint dragPosition;

    ResizeHandle *m_topLeft;
    ResizeHandle *m_topRight;
    ResizeHandle *m_bottomLeft;
    ResizeHandle *m_bottomRight;


private slots:
           void onHandleDragged(ResizeHandle::Corner corner, QPoint delta);
};
#endif // MAINWINDOW_H
