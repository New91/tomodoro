#ifndef BARVIEW_H
#define BARVIEW_H

#include "abstractview.h"


class BarView;

namespace bar_internals {

    class BarWidget : public QWidget {
        Q_OBJECT

    private:
        const BarView*      m_bar_view;

    protected:
        void paintEvent ( QPaintEvent * event );

    public:
        explicit BarWidget(BarView* parent_view);

        QSize sizeHint() const;
    };

};



class QBoxLayout;


class BarView : public AbstractView
{
    Q_OBJECT

private:
    bar_internals::BarWidget*       m_bar_widget;

    QBoxLayout*         m_layout;

    int                 m_length;
    int                 m_width;

    friend class bar_internals::BarWidget;

    void bar_draw(QPainter* p) const ;
    QSize bar_size_hint() const ;

protected:
    void paintEvent ( QPaintEvent * event );

public:
    explicit BarView(QWidget *parent = 0);

public slots:
    virtual void update_settings();

};

#endif // BARVIEW_H
