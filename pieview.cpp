#include "pieview.h"

#include "settings.h"

#include <QPainter>


#include <QMouseEvent>


#include <QApplication>
#include <QDesktopWidget>

PieView::PieView(QWidget *parent) :
    AbstractView(parent)
{
    resize(200, 200);
}


void PieView::paintEvent ( QPaintEvent * event ) {
    QPainter        p(this);

    p.setFont(QFont("Arial", 12));


    p.setBrush(palette().button());
    p.drawPie(0, 0, width() - 1, height() - 1, 16 * 90, 16 * (360.0 * m_current / m_total));

    QRect           text_rect = p.fontMetrics().boundingRect(m_text);

    text_rect.adjust(-5, 0, 0, 0);

    text_rect.moveCenter(QPoint(width() / 2, height() / 2));

    p.drawRect(text_rect);

    p.drawText(text_rect, m_text, QTextOption(Qt::AlignCenter));
}

void PieView::update_settings() {
    AbstractView::update_settings();
}

