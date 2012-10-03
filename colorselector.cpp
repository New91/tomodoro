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


#include "colorselector.h"

#include <QPainter>
#include <QMouseEvent>

#include <QColorDialog>


#include <QLineEdit>

ColorSelector::ColorSelector(QWidget *parent) :
    QWidget(parent),
    //QString(),
    m_color(),
    m_attached_edit()
{
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
}

void ColorSelector::paintEvent ( QPaintEvent * ) {
    QPainter    p(this);

    if(m_color.isValid()) {
        p.setBrush(m_color);
    }

    p.drawRect(0, 0, width() - 1, height() - 1);

    if(!m_color.isValid()) {
        const QRect r = rect();
        p.drawLine(r.topLeft(), r.bottomRight());
        p.drawLine(r.topRight(), r.bottomLeft());
    }
}

void ColorSelector::mouseReleaseEvent ( QMouseEvent * event ) {
    if(rect().contains(event->pos())) {
        QColor n = QColorDialog::getColor(m_color, this);
        if(n.isValid()) {
            set_new_color( n );
        }
    }
}

QSize ColorSelector::sizeHint() const  {
    return QSize(30, 30);
}

////////////////////////

void ColorSelector::set_new_color(QColor n, bool update_edit) {
    if(n != m_color) {
        m_color = n;

        update();

        if(m_attached_edit && update_edit) {
            m_attached_edit->setText(m_color.name());
        }
    }
}

void ColorSelector::attached_text_changed(QString name) {
    set_new_color(name, false);
}

QLineEdit* ColorSelector::attachedEdit() {
    if(!m_attached_edit) {
        m_attached_edit = new QLineEdit;

        connect(m_attached_edit, SIGNAL(textChanged(QString)),
                this, SLOT(attached_text_changed(QString)));

        connect(m_attached_edit, SIGNAL(destroyed()), this, SLOT(deleteLater()));       // remove that?
        connect(this, SIGNAL(destroyed()), m_attached_edit, SLOT(deleteLater()));
    }

    return m_attached_edit;
}
