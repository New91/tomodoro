#include "pieview.h"

#include <QPainter>

#include <QMouseEvent>

PieView::PieView(QWidget *parent) :
    QWidget(parent, Qt::FramelessWindowHint| Qt::WindowStaysOnTopHint | Qt::Dialog),
    m_mouse_anchor(),
    m_win_anchor(),
    m_conf_buzz_dev(5,5),
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

    p.setFont(QFont("Arial", 12));


    p.setBrush(palette().button());
    p.drawPie(0, 0, width() - 1, height() - 1, 16 * 90, 16 * (360.0 * m_current / m_total));

    QRect           text_rect = p.fontMetrics().boundingRect(m_text);

    text_rect.adjust(-5, 0, 0, 0);

    text_rect.moveCenter(QPoint(width() / 2, height() / 2));

    p.drawRect(text_rect);

    p.drawText(text_rect, m_text, QTextOption(Qt::AlignCenter));
}

void PieView::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        m_mouse_anchor = event->globalPos();
    }
}

void PieView::mouseMoveEvent(QMouseEvent* event) {
    if(event->buttons() & Qt::LeftButton) {
        QPoint  n = event->globalPos();

        if(is_buzzing()) {
            m_win_anchor += n - m_mouse_anchor;
        } else {
            move(pos() + n - m_mouse_anchor);
        }

        m_mouse_anchor = n;
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

    //
    // Handle buzzing
    //

    const bool buzzing = is_buzzing();              // current state

    m_current = current;
    m_total = total;

    const bool about_to_buzz = is_buzzing();        // new state


    if(about_to_buzz) {
        // If we're gonna buzz, then offset the window

        if(buzzing) {
            move(m_win_anchor + QPoint(qrand() % (m_conf_buzz_dev.x() * 2 + 1), qrand() % (m_conf_buzz_dev.y() * 2 + 1)) - m_conf_buzz_dev);
        }else {
            m_win_anchor = pos();
        }

    } else if(buzzing) {
        // Buzzing has just turned off.
        move(m_win_anchor);
    }

    //
    // Handle repaint
    //

    // Redraw unless we're in the middle of buzzing
    if( !(buzzing && about_to_buzz) ) {
        int remaining = m_total - m_current;
        m_text = QString("%1:%2")
                 .arg(QString::number(remaining / 60), 2, '0')
                 .arg(QString::number(remaining % 60), 2, '0');

        update();
    }
}
