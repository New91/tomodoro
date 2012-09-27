#include "colorselector.h"

#include <QPainter>
#include <QMouseEvent>

#include <QColorDialog>


#include <QLineEdit>

ColorSelector::ColorSelector(QWidget *parent) :
    QWidget(parent),
    //QString(),
    m_color(),
    m_attached_edit(NULL)
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

        if(m_attached_edit != NULL && update_edit) {
            m_attached_edit->setText(m_color.name());
        }
    }
}

void ColorSelector::attached_text_changed(QString name) {
    set_new_color(name, false);
}

QLineEdit* ColorSelector::attachedEdit() {
    if(m_attached_edit == NULL) {
        m_attached_edit = new QLineEdit;

        connect(m_attached_edit, SIGNAL(textChanged(QString)),
                this, SLOT(attached_text_changed(QString)));

        connect(m_attached_edit, SIGNAL(destroyed()), this, SLOT(deleteLater()));
        connect(this, SIGNAL(destroyed()), m_attached_edit, SLOT(deleteLater()));
    }

    return m_attached_edit;
}
