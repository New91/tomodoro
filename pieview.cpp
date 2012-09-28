#include "pieview.h"

#include <QPainter>


#include <QMouseEvent>


#include <QApplication>
#include <QDesktopWidget>


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

        const int start = 16 * 90 * ((m_settings.flags & PIE_DIRECTION_MASK) ^ 1);

        int span = 16 * (360.0 * m_current / m_total);

        if(m_settings.flags & PIE_INVERTED) span -= 16 * 360;
        if(m_settings.flags & PIE_CLOCKWISE) span = -span;

        p.drawPie(0, 0, width() - 1, height() - 1, start, span);
    }

    QRect           text_rect = p.fontMetrics().boundingRect(m_text);

    text_rect.adjust(-5, 0, 0, 0);



    //text_rect.moveCenter(QPoint(width() / 2, height() / 2));
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

    m_settings.border       = default_to_text((QColor)s.pie.border);
    m_settings.text_border  = default_to_text((QColor)s.pie.text_border);
    m_settings.text_color   = default_to_text((QColor)s.pie.text_color);
    m_settings.filling      = default_to_button((QColor)s.pie.filling);
    m_settings.text_filling = default_to_button((QColor)s.pie.text_filling);

    m_settings.text_size    = s.pie.text_size;

    m_settings.flags = s.pie.direction1;
    if(s.pie.direction2 != 0) m_settings.flags |= PIE_CLOCKWISE;
    if(s.pie.inverted   != 0) m_settings.flags |= PIE_INVERTED;

    const int d = s.pie.radius * 2;
    resize(d, d);

    update();
}

