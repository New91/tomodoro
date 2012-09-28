#ifndef PIEVIEW_H
#define PIEVIEW_H

#include "abstractview.h"

#include "settings.h"

class PieView : public AbstractView
{
    Q_OBJECT

private:

    enum flags_t {
        PIE_RIGHT           = 0,
        PIE_TOP             = 1,
        PIE_LEFT            = 2,
        PIE_BOTTOM          = 3,

        PIE_DIRECTION_MASK  = 3,

        PIE_CLOCKWISE       = 4,
        PIE_INVERTED        = 8
    };

    struct {
        int     text_size;

        int     flags;

#define PIE_COLOR(name, member) QColor member;
        PIE_COLORS
#undef PIE_COLOR
    } m_settings;


protected:
    void paintEvent ( QPaintEvent * event );

public:
    explicit PieView(QWidget *parent = 0);
    
public slots:
    virtual void update_settings();

};

#endif // PIEVIEW_H
