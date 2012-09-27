#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

class AbstractView : public QWidget
{
    Q_OBJECT

private:
    QPoint      m_mouse_anchor;     // mouse cursor anchor (for handling dragging)
    QPoint      m_win_anchor;       // buzzing anchor

    int         m_conf_buzz_dev;    // buzz deviation

    // NOTE: if (m_current == m_total) then we're in buzz mode

    qreal       m_op_normal;        // normal opacity
    qreal       m_op_focused;       // focused opacity

    bool is_buzzing() const {
        return m_current == m_total;
    }

protected:
    int         m_current;          // seconds passed so far
    int         m_total;            // total seconds to pass

    QString     m_text;             // precalculated from current/total

protected:
    void paintEvent ( QPaintEvent * event ) = 0;

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

protected:
    explicit AbstractView(QWidget *parent = 0);

    
public slots:
    void tick(int current, int total);
    virtual void update_settings();
    
};

#endif // ABSTRACTVIEW_H
