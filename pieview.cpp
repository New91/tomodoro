#include "pieview.h"

#include <QPainter>


#include <QDebug>

PieView::PieView(QWidget *parent) :
    AbstractView(parent)
{
    update_settings();
}


void PieView::paintEvent ( QPaintEvent * ) {
    QPainter        p(this);

    p.setFont(QFont("Arial", m_settings.text_size));


    {
        // drow a pie
        p.setPen  (m_settings.border);
        p.setBrush(m_settings.filling);

        const int start = 16 * 90 * ((m_settings.flags & VIEW_DIRECTION_MASK) ^ 1);

        int span = 16 * (360.0 * m_current / m_total);

        if(m_settings.flags & VIEW_INVERTED) span -= 16 * 360;
        if(m_clockwise) span = -span;

        p.drawPie(rect().adjusted(0, 0, -1, -1), start, span);
    }

    QRect  text_rect = p.fontMetrics().boundingRect(m_text).adjusted(-5, 0, 0, 0);

    text_rect.moveCenter(rect().center());

    p.setPen  (m_settings.text_border);
    p.setBrush(m_settings.text_filling);
    p.drawRect(text_rect);

    p.setPen  (m_settings.text_color);
    p.drawText(text_rect, m_text, QTextOption(Qt::AlignCenter));
}

void PieView::update_settings() {
    AbstractView::update_settings();

    Settings        s;

    m_clockwise = s.pie.grow_dir != 0;

    const int d = s.pie.radius * 2;
    resize(d, d);
}

