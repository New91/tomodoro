#ifndef PIEVIEW_H
#define PIEVIEW_H

#include "abstractview.h"

class PieView : public AbstractView
{
    Q_OBJECT

protected:
    void paintEvent ( QPaintEvent * event );

public:
    explicit PieView(QWidget *parent = 0);
    
public slots:
    void update_settings();

};

#endif // PIEVIEW_H
