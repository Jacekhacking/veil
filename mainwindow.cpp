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

    setStyleSheet("background-color: rgba(0,80,255,160);");


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
