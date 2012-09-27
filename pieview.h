#ifndef PIEVIEW_H
#define PIEVIEW_H

#include "abstractview.h"

class PieView : public AbstractView
{
    Q_OBJECT

private:

    struct {
        QColor      border;
        QColor      filling;
    } m_settings;

    QColor default_to_text(QColor c) const {
        return c.isValid() ? c : palette().text().color();
    }

    QColor default_to_button(QColor c) const {
        return c.isValid() ? c : palette().button().color();
    }


protected:
    void paintEvent ( QPaintEvent * event );

public:
    explicit PieView(QWidget *parent = 0);
    
public slots:
    virtual void update_settings();

};

#endif // PIEVIEW_H
