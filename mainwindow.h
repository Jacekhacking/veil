#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QRect>
#include <QWidget>

#include "handlelayer.h"

/*
 * The tint itself: a full-screen layer-shell surface that is transparent for
 * input end to end, so it never intercepts a click. Only the sub-rectangle
 * veilRect() is painted; the rest of the surface stays fully transparent.
 *
 * Resizing therefore never touches the surface -- it just repaints a smaller
 * or larger rectangle inside a surface that is always the size of the screen.
 */
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

    /// Realise the QWindow so LayerShellQt has something to attach to.
    void initLayerShell() { create(); }

    QRect veilRect() const { return m_rect; }

public slots:
    void setVeilRect(const QRect &rect);
    void onCornerMoved(HandleLayer::Corner corner, QPoint pos);
    void onWindowMoved(QPoint pos);

signals:
    void veilRectChanged(const QRect &rect);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QRect m_rect;
};

#endif // MAINWINDOW_H
