#include "pieview.h"

#include <QPainter>

#include <QMouseEvent>

PieView::PieView(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint | Qt::Dialog),
    m_anchor(),
    m_current(0),
    m_total(100)
{
    setAttribute(Qt::WA_TranslucentBackground);

    setWindowOpacity(0.7);

    resize(200, 200);

    setContextMenuPolicy(Qt::CustomContextMenu);
}


void PieView::paintEvent ( QPaintEvent * event ) {
    QPainter        p(this);

    p.setBrush(palette().button());
    p.drawPie(0, 0, width() - 1, height() - 1, 16 * 90, 16 * (360.0 * m_current / m_total));
}

void PieView::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        m_anchor = event->globalPos();
    }
}

void PieView::mouseMoveEvent(QMouseEvent* event) {
    if(event->buttons() & Qt::LeftButton) {
        QPoint  n = event->globalPos();

        move(pos() + n - m_anchor);
        m_anchor = n;
    }
}

void PieView::enterEvent(QEvent *) {
    setWindowOpacity(0.8);
}


void PieView::leaveEvent(QEvent *) {
    setWindowOpacity(0.5);
}




//////////////////////////////////////////

void PieView::tick(int current, int total) {
    qDebug("ticked!");

    m_current = current;
    m_total = total;

    update();
}
