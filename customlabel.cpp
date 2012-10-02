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


#include "customlabel.h"

#include "settings.h"



#include <QPainter>





CustomLabel::CustomLabel(QWidget *parent) :
    QWidget(parent),
    m_text("--:--"),
    m_size_hint(20, 20),
    m_font_size(10)
{
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}


void CustomLabel::paintEvent ( QPaintEvent * ) {
    QPainter        p(this);

    p.drawRect(rect().adjusted(0, 0, -1, -1));


    p.setFont(QFont("Arial", m_font_size));

    QRect  text_rect = p.fontMetrics()
            .boundingRect(m_text).adjusted(-5, 0, 0, 0);

    if(text_rect.width() > width() || text_rect.height() > height()) {
        m_size_hint = text_rect.size();

        updateGeometry();

        // We assume will resize the widget which will trigger a repaint again.
        // So we just quit now.
        return;
    }

    QRect   adj = rect().adjusted(0, 0, -1, -1);

    p.setPen  (m_colors.border);
    p.setBrush(m_colors.bkg);
    p.drawRect(adj);

    p.setPen  (m_colors.text);
    p.drawText(rect(), m_text, QTextOption(Qt::AlignCenter));
}

QSize CustomLabel::sizeHint() const {
    return m_size_hint;
}


//////////////////////////////////////////////////

void CustomLabel::setText ( const QString & new_text ) {
    m_text = new_text;
    update();
}

void CustomLabel::update_settings() {
    Settings        s;

    m_font_size     = s.view.text_size;

    m_colors.text   = s.defaultToText(this, (QColor)s.view.text_color);
    m_colors.border = s.defaultToText(this, (QColor)s.view.text_border);
    m_colors.bkg    = s.defaultToButton(this, (QColor)s.view.text_filling);

    update();
}
