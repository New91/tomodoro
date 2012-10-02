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
    ~PieView();

public slots:
    virtual void update_settings();

};

#endif // PIEVIEW_H
