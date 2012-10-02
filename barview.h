/*
 *  Copyright 2012 Yury Makarevich
 *
 *  This file is part of Tomodoro.
 *
 *  Tomodoro is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Tomodoro is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Tomodoro.  If not, see <http://www.gnu.org/licenses/>.
 */


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
    ~BarView();

public slots:
    virtual void update_settings();

};

#endif // BARVIEW_H
