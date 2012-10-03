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


#ifndef COLORSELECTOR_H
#define COLORSELECTOR_H

#include <QWidget>

#include <QPointer>

class QLineEdit;

class ColorSelector : public QWidget
{
    Q_OBJECT

private:

    QColor                  m_color;

    QPointer<QLineEdit>     m_attached_edit;

    void set_new_color(QColor n, bool update_edit = true);

protected:
    void paintEvent ( QPaintEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event ) ;
    QSize sizeHint() const ;

private slots:
    void attached_text_changed(QString);
    
public:
    explicit ColorSelector(QWidget *parent = 0);

    QLineEdit*  attachedEdit();

    QColor color() const {
        return m_color;
    }
};

#endif // COLORSELECTOR_H
