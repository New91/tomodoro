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


    p.setPen  (m_settings.border);
    p.setBrush(m_settings.filling);
    p.drawPie(0, 0, width() - 1, height() - 1, 16 * 90, 16 * (360.0 * m_current / m_total));

    QRect           text_rect = p.fontMetrics().boundingRect(m_text);

    text_rect.adjust(-5, 0, 0, 0);

    text_rect.moveCenter(QPoint(width() / 2, height() / 2));

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


    {
        int d = s.pie.radius * 2;

        resize(d, d);
    }

    update();
}

