#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

#include "settings.h"

class AbstractView : public QWidget
{
    Q_OBJECT

private:
    QPoint      m_mouse_anchor;     // mouse cursor anchor (for handling dragging)
    QPoint      m_win_anchor;       // buzzing anchor

    int         m_conf_buzz_dev;    // buzz deviation

    qreal       m_op_normal;        // normal opacity
    qreal       m_op_focused;       // focused opacity

    //
    // a couple of utilities
    //

    // NOTE: if (m_current == m_total) then we're in buzz mode
    bool is_buzzing() const {
        return m_current == m_total;
    }

    QColor default_to_text(QColor c) const {
        return c.isValid() ? c : palette().text().color();
    }

    QColor default_to_button(QColor c) const {
        return c.isValid() ? c : palette().button().color();
    }

protected:
    enum flags_t {
        VIEW_RIGHT           = 0,
        VIEW_TOP             = 1,
        VIEW_LEFT            = 2,
        VIEW_BOTTOM          = 3,

        VIEW_DIRECTION_MASK  = 3,

        VIEW_INVERTED        = 4
    };

    struct {
        int         text_size;      // text size
        int         flags;          // main dir and invertion flag

#define VIEW_COLOR(name, member) QColor member;
        VIEW_COLORS
#undef VIEW_COLOR
    } m_settings;

    //
    // current state
    //

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
