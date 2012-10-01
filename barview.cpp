#include "barview.h"

#include <QPainter>


BarView::BarView(QWidget *parent) :
    AbstractView(parent)
{
    update_settings();
}

void BarView::paintEvent ( QPaintEvent * ) {
    QPainter        p(this);

    //p.setFont(QFont("Arial", m_settings.text_size));

    //
    // make sure the widget has proper geometry
    //

    /*
    QRect   text_rect = p.fontMetrics().boundingRect(m_text).adjusted(-5, 0, 0, 0);

    {
        int     w, h;

        if(((m_settings.flags & VIEW_DIRECTION_MASK) & 1) == 0) {       // is horizontal ?
            h = text_rect.height() + m_length;
            w = qMax(text_rect.width(), m_width);
        } else {
            w = text_rect.width() + m_length;
            h = qMax(text_rect.height(), m_width);
        }

        if(width() < w || height() < h) {
            resize(w, h);
            return;
        }
    }

    //
    // if the geometry is ok, do the actual painting
    //

    QRect   main = rect().adjusted(0, 0, -1, -1);
    QRect   bar  = main;

    switch(m_settings.flags & VIEW_DIRECTION_MASK) {
    case 0: {
        text_rect.moveBottomLeft(QPoint(0, main.bottom()));
        bar.setBottom(text_rect.top());

        int dw = bar.width() - m_width;
        int dw2 = dw / 2;

        bar.adjust(dw2, 0, dw2 - dw, 0);
    } break;
    case 2: {
        text_rect.moveTopLeft(QPoint(0, main.top()));
        bar.setTop(text_rect.bottom());

        int dw = bar.width() - m_width;
        int dw2 = dw / 2;

        bar.adjust(dw2, 0, dw2 - dw, 0);
    } break;
    case 1: {
        text_rect.moveTopLeft(QPoint(0, 0));
        bar.setLeft(text_rect.right());

        int dw = bar.height() - m_width;
        int dw2 = dw / 2;

        bar.adjust(0, dw2, 0, dw2 - dw);
    } break;
    case 3: {
        text_rect.moveTopRight(QPoint(main.right(), 0));
        text_rect.moveRight(main.right());
        bar.setRight(text_rect.left());

        int dw = bar.height() - m_width;
        int dw2 = dw / 2;

        bar.adjust(0, dw2, 0, dw2 - dw);
    } break;
    }

    p.setPen  (m_settings.border);
    p.setBrush(m_settings.filling);
    p.drawRect(bar);

    p.setPen  (m_settings.text_border);
    p.setBrush(m_settings.text_filling);
    p.drawRect(text_rect);

    p.setPen  (m_settings.text_color);
    p.drawText(text_rect, m_text, QTextOption(Qt::AlignCenter));
    */
}

void BarView::update_settings() {
    AbstractView::update_settings();

    Settings        s;

    m_length = s.bar.length;
    m_width  = s.bar.width;

    {
        // downsize enough to trigger proper resize during next repaint
        const int d = qMin(m_length, m_width);

        resize(d, d);
    }
}
