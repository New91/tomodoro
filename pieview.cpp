#include "pieview.h"

#include "customlabel.h"

#include <QPainter>
#include <QHBoxLayout>

#include <QDebug>

PieView::PieView(QWidget *parent) :
    AbstractView(parent)
{
    update_settings();

    QBoxLayout*     lo = new QHBoxLayout(this);

    lo->addWidget(customLabel());
}


void PieView::paintEvent ( QPaintEvent * ) {
    QPainter        p(this);

    // draw a pie
    p.setPen  (m_settings.border);
    p.setBrush(m_settings.filling);

    const int start = 16 * 90 * ((m_settings.flags & VIEW_DIRECTION_MASK) ^ 1);

    int span = 16 * (360.0 * m_current / m_total);

    if(m_settings.flags & VIEW_INVERTED) span -= 16 * 360;
    if(m_clockwise) span = -span;

    p.drawPie(rect().adjusted(0, 0, -1, -1), start, span);
}

void PieView::update_settings() {
    AbstractView::update_settings();

    Settings        s;

    m_clockwise = s.pie.grow_dir != 0;

    const int d = s.pie.radius * 2;
    resize(d, d);
}

