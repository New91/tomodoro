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


#include "settingsdialog.h"


#include "colorselector.h"

#include <QMessageBox>

#include <QBoxLayout>
#include <QFormLayout>

#include <QTabWidget>
#include <QGroupBox>
#include <QPushButton>
#include <QDialogButtonBox>

#include <QLineEdit>
#include <QComboBox>

#include <QIntValidator>
#include <QDoubleValidator>








SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    /////////////////////////////////////

    QTabWidget*         tabs = new QTabWidget;

    {
        QFrame*         fr   = new QFrame;
        QBoxLayout*     gr_layout = new QVBoxLayout(fr);

        {
            QGroupBox*      gr   = new QGroupBox("General");
            QFormLayout*    form = new QFormLayout(gr);

            form->addRow("M&ain timeout (min)", m_common.timeout = new QLineEdit);
            form->addRow("&Default view", m_common.default_view = new QComboBox);

            m_common.default_view->addItem("Pie");
            m_common.default_view->addItem("Bar");

            m_common.timeout->setValidator(new QIntValidator(1, 60 * 24, this));

            gr_layout->addWidget(gr);
        }

        {
            QGroupBox*      gr   = new QGroupBox("Pie");
            QFormLayout*    form = new QFormLayout(gr);

            form->addRow("&Radius (px)",        m_pie.radius = new QLineEdit);
            form->addRow("&Growth direction",   m_pie.grow_dir = new QComboBox);

            m_pie.grow_dir->addItem("Counterclockwise");
            m_pie.grow_dir->addItem("Clockwise");

            m_pie.radius->setValidator(new QIntValidator(10, 1000, this));

            gr_layout->addWidget(gr);
        }

        {
            QGroupBox*      gr   = new QGroupBox("Bar");
            QFormLayout*    form = new QFormLayout(gr);

            form->addRow("&Length (px)", m_bar.length = new QLineEdit);
            form->addRow("&Width (px)",  m_bar.width  = new QLineEdit);

            m_bar.length->setValidator(new QIntValidator(10, 500, this));
            m_bar.width ->setValidator(new QIntValidator(10, 500, this));

            gr_layout->addWidget(gr);
        }

        tabs->addTab(fr, "&Misc");
    }

    {
        QFrame*         fr   = new QFrame;
        QFormLayout*    form = new QFormLayout(fr);

        form->addRow("View default &opacity (%)", m_view.op_normal = new QLineEdit);
        form->addRow("View &focus opacity (%)",  m_view.op_focused = new QLineEdit);

        form->addRow("Buzz &interval (ms)",     m_view.buzz_int = new QLineEdit);
        form->addRow("Buzz devia&tion (px)",    m_view.buzz_dev = new QLineEdit);
        form->addRow("Fo&nt size (px)",         m_view.text_size = new QLineEdit);

        form->addRow("Main dir&ection",         m_view.main_dir = new QComboBox);
        form->addRow("&Behaviour",              m_view.inverted = new QComboBox);

        m_view.main_dir->addItem("Top");
        m_view.main_dir->addItem("Right");
        m_view.main_dir->addItem("Bottom");
        m_view.main_dir->addItem("Left");

        m_view.inverted->addItem("Waxing");
        m_view.inverted->addItem("Waning");


        m_view.op_normal->setValidator (new QIntValidator(1, 100, this));
        m_view.op_focused->setValidator(new QIntValidator(1, 100, this));

        m_view.buzz_int->setValidator(new QIntValidator(10, 1000, this));
        m_view.buzz_dev->setValidator(new QIntValidator(0, 100, this));
        m_view.text_size->setValidator(new QIntValidator(5, 30, this));

        tabs->addTab(fr, "&View");
    }

    {
        QFrame*         fr   = new QFrame;
        QFormLayout*    form = new QFormLayout(fr);

#define VIEW_COLOR(name, member)                            \
        {                                                       \
            ColorSelector*  sel = new ColorSelector;            \
            QBoxLayout*     l = new QHBoxLayout;                \
            l->addWidget(m_view.member = sel->attachedEdit());   \
            l->addWidget(sel);                                  \
            form->addRow(name, l);                              \
        }

        VIEW_COLORS;

#undef VIEW_COLOR

        tabs->addTab(fr, "&Colors");
    }

    QBoxLayout* main_layout = new QVBoxLayout(this);

    main_layout->addWidget(tabs);

    main_layout->addStretch();

    {
        QDialogButtonBox*   button_box =
                new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel | QDialogButtonBox::Apply, Qt::Horizontal, this);

        connect(button_box, SIGNAL(accepted()), SLOT(on_accept()));
        connect(button_box, SIGNAL(rejected()), SLOT(reject()));
        connect(button_box->button(QDialogButtonBox::Apply), SIGNAL(clicked()), SLOT(on_apply()));

        main_layout->addWidget(button_box);
    }

    ////

    load_configuration();
}

void SettingsDialog::load_configuration() {
    Settings        s;

    m_common.timeout->setText(QString::number(s.interval));
    m_common.default_view->setCurrentIndex(s.default_view);

    m_view.op_normal ->setText(QString::number(s.view.op_normal));
    m_view.op_focused->setText(QString::number(s.view.op_focused));

    m_view.buzz_int->setText(QString::number(s.view.buzz_int));
    m_view.buzz_dev->setText(QString::number(s.view.buzz_dev));
    m_view.text_size->setText(QString::number(s.view.text_size));

    m_view.main_dir ->setCurrentIndex(s.view.main_dir);
    m_view.inverted ->setCurrentIndex(s.view.inverted);

#define VIEW_COLOR(name, member) m_view.member->setText(s.view.member);
    VIEW_COLORS;
#undef VIEW_COLOR

    m_pie.radius->setText(QString::number(s.pie.radius));
    m_pie.grow_dir->setCurrentIndex(s.pie.grow_dir);

    m_bar.length->setText(QString::number(s.bar.length));
    m_bar.width ->setText(QString::number(s.bar.width));
}

bool SettingsDialog::store_configuration() {
    /*
    //
    // Do not trust double validators
    //

    qreal op_normal  = m_view.op_normal->text().toInt();
    qreal op_focused = m_view.op_focused->text().toInt();

    if(op_normal < 0.0 || op_normal > 1.0) {
        QMessageBox::warning(this, "Validation error", "View opacity must lie within 0.0 and 1.0");
        m_view.op_normal->setFocus();
        return false;
    }

    if(op_focused < 0.0 || op_focused > 1.0) {
        QMessageBox::warning(this, "Validation error", "View opacity must lie within 0.0 and 1.0");
        m_view.op_focused->setFocus();
        return false;
    }
    */


    //
    // Store the settings, if everything's ok
    //

    Settings        s;

    s.interval          = m_common.timeout->text().toInt();
    s.default_view      = m_common.default_view->currentIndex();

    s.view.buzz_int     = m_view.buzz_int->text().toInt();
    s.view.buzz_dev     = m_view.buzz_dev->text().toInt();
    s.view.text_size    = m_view.text_size->text().toInt();

    s.view.main_dir     = m_view.main_dir->currentIndex();
    s.view.inverted     = m_view.inverted->currentIndex();

#define VIEW_COLOR(name, member) s.view.member = m_view.member->text();
    VIEW_COLORS;
#undef VIEW_COLOR

    s.pie.radius    = m_pie.radius->text().toInt();
    s.pie.grow_dir  = m_pie.grow_dir->currentIndex();

    s.bar.length    = m_bar.length->text().toInt();
    s.bar.width     = m_bar.width ->text().toInt();

    s.view.op_normal  = m_view.op_normal->text().toInt();
    s.view.op_focused = m_view.op_focused->text().toInt();

    emit settingsApplied();

    return true;
}



void SettingsDialog::on_accept() {
    if(store_configuration()) {
        accept();
    }
}

void SettingsDialog::on_apply() {
    store_configuration();
}
