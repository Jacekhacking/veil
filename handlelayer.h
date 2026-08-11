#ifndef HANDLELAYER_H
#define HANDLELAYER_H

#include <QRect>
#include <QRegion>
#include <QWidget>

/*
 * A full-screen layer-shell surface that exists only to carry the four corner
 * grips. Its input region is masked down to the grips themselves, so every
 * click that does not land on a red box goes straight through to whatever is
 * underneath -- including clicks inside the tinted area.
 *
 * Keeping the surface full-screen (instead of moving four small surfaces
 * around) means we never have to ask the compositor to reposition anything:
 * a layer-shell client cannot place itself freely, and dragging a surface via
 * anchor margins lags a round-trip behind the pointer. Here the surface is
 * nailed to the screen and only the painted contents move, so the grips track
 * the pointer exactly.
 */
class HandleLayer : public QWidget
{
    Q_OBJECT

public:
    enum Corner {
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight
    };
    Q_ENUM(Corner)

    static constexpr int HandleSize = 24;

    explicit HandleLayer(QWidget *parent = nullptr);

    /// Realise the QWindow so LayerShellQt has something to attach to.
    void initLayerShell() { create(); }

public slots:
    void setRect(const QRect &rect);

signals:
    /// Where the user wants this corner to sit, in surface (== screen) coordinates.
    void cornerMoved(HandleLayer::Corner corner, QPoint pos);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    QRect handleRect(Corner corner) const;
    QPoint cornerPoint(Corner corner) const;
    QRegion handleRegion() const;
    void updateInputRegion();

    QRect m_rect;
    Corner m_active = TopLeft;
    QPoint m_grabOffset;
    bool m_dragging = false;
};

#endif // HANDLELAYER_H
