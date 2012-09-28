#ifndef PIEVIEW_H
#define PIEVIEW_H

#include "abstractview.h"

#include "settings.h"

class PieView : public AbstractView
{
    Q_OBJECT

private:

    struct {
        int     text_size;

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
