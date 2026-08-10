#include "resizehandle.h"
#include <QMouseEvent>

ResizeHandle::ResizeHandle( Corner corner, QWidget *parent)
    : QWidget{parent},
    m_corner(corner)
{
    setFixedSize(100, 100);
    setAttribute(Qt::WA_TranslucentBackground);
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setCursor(Qt::SizeFDiagCursor);
    setStyleSheet("background-color: rgba(255,0,0, 255);");

}

void ResizeHandle::mousePressEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton){
        m_dragging = true;
        m_dragStart = event->globalPosition().toPoint();
    }
}

void ResizeHandle::mouseMoveEvent(QMouseEvent *event){
    if(m_dragging){
        QPoint current = event->globalPosition().toPoint();
        QPoint delta = current - m_dragStart;
        m_dragStart = current;
        emit dragged(m_corner, delta);
    }

}

void ResizeHandle::mouseReleaseEvent(QMouseEvent *event){
    if(event->button() == Qt::LeftButton)
        m_dragging = false;
}
