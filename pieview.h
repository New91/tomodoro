#ifndef PIEVIEW_H
#define PIEVIEW_H

#include "abstractview.h"

class PieView : public AbstractView
{
    Q_OBJECT

private:

    bool        m_clockwise;        // clockwise setting

protected:
    void paintEvent ( QPaintEvent * event );

public:
    explicit PieView(QWidget *parent = 0);
    
public slots:
    virtual void update_settings();

};

#endif // PIEVIEW_H
