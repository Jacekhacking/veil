#include "mainwindow.h"

#include <QPainter>

namespace {
// Never let the veil shrink below the point where the four grips would overlap.
constexpr int MinVeilSize = HandleLayer::HandleSize * 2 + 8;
}

MainWindow::MainWindow(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowTransparentForInput);
    setAttribute(Qt::WA_TranslucentBackground);
}

void MainWindow::setVeilRect(const QRect &rect)
{
    if (m_rect == rect)
        return;

    m_rect = rect;
    update();
    emit veilRectChanged(m_rect);
}

void MainWindow::onCornerMoved(HandleLayer::Corner corner, QPoint pos)
{
    QRect g = m_rect;

    switch (corner) {
    case HandleLayer::TopLeft:
        g.setLeft(qMin(pos.x(), g.right() - MinVeilSize));
        g.setTop(qMin(pos.y(), g.bottom() - MinVeilSize));
        break;
    case HandleLayer::TopRight:
        g.setRight(qMax(pos.x(), g.left() + MinVeilSize));
        g.setTop(qMin(pos.y(), g.bottom() - MinVeilSize));
        break;
    case HandleLayer::BottomLeft:
        g.setLeft(qMin(pos.x(), g.right() - MinVeilSize));
        g.setBottom(qMax(pos.y(), g.top() + MinVeilSize));
        break;
    case HandleLayer::BottomRight:
        g.setRight(qMax(pos.x(), g.left() + MinVeilSize));
        g.setBottom(qMax(pos.y(), g.top() + MinVeilSize));
        break;
    }

    // Keep the whole thing on screen, otherwise a grip can be dragged out of
    // reach and there is no way to get it back.
    setVeilRect(g.intersected(rect()));
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.fillRect(m_rect, QColor(120, 0, 255, 80));
}
