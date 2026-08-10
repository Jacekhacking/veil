#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QLabel>
#include <QMouseEvent>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowTransparentForInput);

    setAttribute(Qt::WA_TranslucentBackground);

    setStyleSheet("background-color: rgba(120,0,255,160);");



}

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        dragPosition = event->globalPosition().toPoint() - frameGeometry().topLeft();
};
void MainWindow::mouseMoveEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        move(event->globalPosition().toPoint() - dragPosition);
};

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::onHandleDragged(ResizeHandle::Corner corner, QPoint delta){
    QRect g = geometry();

    switch(corner){
    case ResizeHandle::TopLeft:
        g.setTopLeft(g.topLeft() + delta);
        break;
    case ResizeHandle::TopRight:
        g.setTopRight(g.topRight() + delta);
        break;
    case ResizeHandle::BottomLeft:
        g.setBottomLeft(g.bottomLeft() + delta);
        break;
    case ResizeHandle::BottomRight:
        g.setBottomRight(g.bottomRight() + delta);
        break;
    }

    setGeometry(g);

}




































