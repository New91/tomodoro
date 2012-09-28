#ifndef BARVIEW_H
#define BARVIEW_H

#include "abstractview.h"



class BarView : public AbstractView
{
    Q_OBJECT

private:

    int         m_length;
    int         m_width;

protected:
    void paintEvent ( QPaintEvent * event );

public:
    explicit BarView(QWidget *parent = 0);

public slots:
    virtual void update_settings();

};

#endif // BARVIEW_H
