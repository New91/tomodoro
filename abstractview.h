#ifndef ABSTRACTVIEW_H
#define ABSTRACTVIEW_H

#include <QWidget>

#include "settings.h"


class CustomLabel;

class AbstractView : public QWidget
{
    Q_OBJECT

private:
    QPoint          m_mouse_anchor;     // mouse cursor anchor (for handling dragging)
    QPoint          m_win_anchor;       // buzzing anchor

    int             m_conf_buzz_dev;    // buzz deviation

    qreal           m_op_normal;        // normal opacity
    qreal           m_op_focused;       // focused opacity


    // custom label (to be properly placed by the child's ctor)
    CustomLabel*    m_custom_label;


    //
    // a couple of utilities
    //

    // NOTE: if (m_current == m_total) then we're in buzz mode
    bool is_buzzing() const {
        return m_current == m_total;
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
        int         flags;          // main dir and invertion flag

        QColor      border;
        QColor      filling;
    } m_settings;

    //
    // current state
    //

    int         m_current;          // seconds passed so far
    int         m_total;            // total seconds to pass


protected:
    void paintEvent ( QPaintEvent * event ) = 0;

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);

protected:
    explicit AbstractView(QWidget *parent = 0);

    CustomLabel* customLabel() const {
        return m_custom_label;
    }

    
public slots:
    void tick(int current, int total);
    virtual void update_settings();
    
};

#endif // ABSTRACTVIEW_H
