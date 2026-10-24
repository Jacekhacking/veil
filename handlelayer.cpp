#include "handlelayer.h"

#include <QMouseEvent>
#include <QPainter>
#include <QWindow>

#include <array>

namespace {
constexpr std::array<HandleLayer::Corner, 4> AllCorners = {
    HandleLayer::TopLeft,
    HandleLayer::TopRight,
    HandleLayer::BottomLeft,
    HandleLayer::BottomRight,
};

Qt::CursorShape cursorFor(HandleLayer::Corner corner)
{
    switch (corner) {
    case HandleLayer::TopLeft:
    case HandleLayer::BottomRight:
        return Qt::SizeFDiagCursor;
    case HandleLayer::TopRight:
    case HandleLayer::BottomLeft:
        return Qt::SizeBDiagCursor;
    }
    return Qt::ArrowCursor;
}
}

HandleLayer::HandleLayer(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    // The mask only covers the grips, so we never see a move event unless the
    // pointer is on one -- but we still need tracking to get them at all.
    setMouseTracking(true);
}

void HandleLayer::setRect(const QRect &rect)
{
    if (m_rect == rect)
        return;

    const QRegion previous = handleRegion();
    m_rect = rect;
    updateInputRegion();
    // Repaint where the grips were as well as where they now are, otherwise the
    // old ones stay in the buffer and the compositor keeps drawing them.
    update(previous | handleRegion());
}

QPoint HandleLayer::cornerPoint(Corner corner) const
{
    switch (corner) {
    case TopLeft:     return m_rect.topLeft();
    case TopRight:    return m_rect.topRight();
    case BottomLeft:  return m_rect.bottomLeft();
    case BottomRight: return m_rect.bottomRight();
    }
    return QPoint();
}

QRect HandleLayer::handleRect(Corner corner) const
{
    // Grips sit inside the veil rect so they stay on screen at the edges.
    const QPoint c = cornerPoint(corner);
    const int dx = (corner == TopLeft || corner == BottomLeft) ? 0 : -(HandleSize - 1);
    const int dy = (corner == TopLeft || corner == TopRight) ? 0 : -(HandleSize - 1);
    return QRect(c + QPoint(dx, dy), QSize(HandleSize, HandleSize));
}

QRegion HandleLayer::handleRegion() const
{
    QRegion region;
    for (Corner corner : AllCorners)
        region += handleRect(corner);
    return region;
}

void HandleLayer::updateInputRegion()
{
    // On Wayland a window mask becomes the surface's input region, which is what
    // makes everything except the grips click-through.
    //
    // This deliberately goes through QWindow rather than QWidget::setMask():
    // the QWidget version additionally clips all painting to the mask, so the
    // grips' old pixels could never be cleared once the mask moved off them and
    // they stayed on screen as ghosts.
    if (QWindow *handle = windowHandle())
        handle->setMask(handleRegion());
}

void HandleLayer::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);
    // The compositor sizes us on the first configure; re-assert the input region
    // so it survives the resize.
    updateInputRegion();
}

void HandleLayer::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    for (Corner corner : AllCorners)
        painter.fillRect(handleRect(corner), QColor(120, 0, 255, 80));
}

void HandleLayer::mousePressEvent(QMouseEvent *event)
{
    if (event->button() != Qt::LeftButton)
        return;

    const QPoint pos = event->position().toPoint();
    for (Corner corner : AllCorners) {
        if (!handleRect(corner).contains(pos))
            continue;

        m_active = corner;
        m_dragging = true;
        m_dragStart = pos;
        // Remember where inside the grip we grabbed, so the corner does not
        // jump to the pointer on the first move.
        m_grabOffset = pos - cornerPoint(corner);
        return;
    }
}

void HandleLayer::mouseMoveEvent(QMouseEvent *event)
{
    const QPoint pos = event->position().toPoint();

    m_shiftHeld = event->modifiers() & Qt::ShiftModifier;

    if (m_dragging) {
    // create delta difference for if shift is pressed to move the entire window
        QPoint delta = pos - m_dragStart;
        m_dragStart = pos;

        if(m_shiftHeld){
            emit windowMoved(delta);
        }
        else{
            emit cornerMoved(m_active, pos - m_grabOffset);
        }
        return;
    }

    for (Corner corner : AllCorners) {
        if (handleRect(corner).contains(pos)) {
            setCursor(cursorFor(corner));
            return;
        }
    }
}

void HandleLayer::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        m_dragging = false;
}
