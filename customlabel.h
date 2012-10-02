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


#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QWidget>

class CustomLabel : public QWidget
{
    Q_OBJECT

private:

    QString         m_text;

    QSize           m_size_hint;

    int             m_font_size;

    struct {
        QColor      bkg;
        QColor      border;
        QColor      text;
    } m_colors;

protected:
    void paintEvent ( QPaintEvent * event );

public:
    QSize sizeHint() const;

public:
    explicit CustomLabel(QWidget *parent = 0);


public slots:
    void setText ( const QString & );
    void update_settings();
};

#endif // CUSTOMLABEL_H
