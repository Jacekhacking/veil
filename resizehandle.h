#ifndef RESIZEHANDLE_H
#define RESIZEHANDLE_H

#include <QWidget>
#include <QPoint>

class ResizeHandle : public QWidget
{
    Q_OBJECT
public:
    enum Corner{
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };

    explicit ResizeHandle(Corner corner, QWidget *parent = nullptr);

    void initLayerShell(){create();}

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



signals:
    void dragged(ResizeHandle::Corner corner, QPoint delta);

private:

    Corner m_corner;
    QPoint m_dragStart;
    bool m_dragging = false;
};

#endif // RESIZEHANDLE_H
