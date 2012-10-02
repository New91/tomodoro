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


#include "pieview.h"

#include "customlabel.h"

#include <QPainter>
#include <QHBoxLayout>

#include <QDebug>

PieView::PieView(QWidget *parent) :
    AbstractView(parent)
{
    update_settings();

    QBoxLayout*     lo = new QHBoxLayout(this);

    lo->addWidget(customLabel());

    move(QSettings().value("pie/pos").toPoint());
}


PieView::~PieView() {
    QSettings().setValue("pie/pos", pos());
}


void PieView::paintEvent ( QPaintEvent * ) {
    QPainter        p(this);

    // draw a pie
    p.setPen  (m_settings.border);
    p.setBrush(m_settings.filling);

    const int start = 16 * 90 * ((m_settings.flags & VIEW_DIRECTION_MASK) ^ 1);

    int span = 16 * (360.0 * m_current / m_total);

    if(m_settings.flags & VIEW_INVERTED) span -= 16 * 360;
    if(m_clockwise) span = -span;

    p.drawPie(rect().adjusted(0, 0, -1, -1), start, span);
}

void PieView::update_settings() {
    AbstractView::update_settings();

    Settings        s;

    m_clockwise = s.pie.grow_dir != 0;

    const int d = s.pie.radius * 2;
    resize(d, d);
}

