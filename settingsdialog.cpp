#include "settingsdialog.h"


#include "settings.h"

#include "colorselector.h"

#include <QMessageBox>

#include <QBoxLayout>
#include <QFormLayout>

#include <QTabWidget>
#include <QGroupBox>
#include <QDialogButtonBox>

#include <QLineEdit>

#include <QIntValidator>
#include <QDoubleValidator>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    /////////////////////////////////////

    QBoxLayout*         main_layout = new QVBoxLayout(this);

    {
        QGroupBox*      gr   = new QGroupBox("Common");
        QFormLayout*    form = new QFormLayout(gr);

        form->addRow("&Main timeout (min)", m_common.timeout = new QLineEdit);

        m_common.timeout->setValidator(new QIntValidator(1, 60 * 24, this));

        main_layout->addWidget(gr);
    }

    {
        QGroupBox*      gr   = new QGroupBox("View");
        QFormLayout*    form = new QFormLayout(gr);

        form->addRow("View &default opacity (ratio)", m_view.op_normal = new QLineEdit);
        form->addRow("View &focus opacity (ratio)",  m_view.op_focused = new QLineEdit);

        form->addRow("Buzz &interval (ms)",  m_view.buzz_int = new QLineEdit);
        form->addRow("Buzz d&eviation (px)", m_view.buzz_dev = new QLineEdit);

        m_view.op_normal->setValidator (new QDoubleValidator(0.0, 1.0, 3, this));
        m_view.op_focused->setValidator(new QDoubleValidator(0.0, 1.0, 3, this));

        m_view.buzz_int->setValidator(new QIntValidator(10, 1000, this));
        m_view.buzz_dev->setValidator(new QIntValidator(0, 100, this));

        main_layout->addWidget(gr);
    }

    {
        QGroupBox*      gr   = new QGroupBox("Pie");
        QFormLayout*    form = new QFormLayout(gr);

#define COLOR_SELECTOR(name, member)                        \
        {                                                   \
            ColorSelector*  sel = new ColorSelector;        \
            QBoxLayout*     l = new QHBoxLayout;            \
            l->addWidget((member) = sel->attachedEdit());   \
            l->addWidget(sel);                              \
            form->addRow((name), l);                        \
        }

        COLOR_SELECTOR("Border",  m_pie.border);
        COLOR_SELECTOR("Filling", m_pie.filling);

#undef COLOR_SELECTOR

        main_layout->addWidget(gr);
    }

    main_layout->addStretch();

    {
        QDialogButtonBox*   button_box =
                new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, Qt::Horizontal, this);

        connect(button_box, SIGNAL(accepted()), SLOT(on_accept()));
        connect(button_box, SIGNAL(rejected()), SLOT(reject()));

        main_layout->addWidget(button_box);
    }

    ////

    load_configuration();
}

void SettingsDialog::load_configuration() {
    Settings        s;

    m_common.timeout->setText(QString::number(s.interval));

    m_view.op_normal ->setText(QString::number(s.view.op_normal));
    m_view.op_focused->setText(QString::number(s.view.op_focused));

    m_view.buzz_int->setText(QString::number(s.view.buzz_int));
    m_view.buzz_dev->setText(QString::number(s.view.buzz_dev));

    m_pie.border ->setText(s.pie.border);
    m_pie.filling->setText(s.pie.filling);
}

void SettingsDialog::on_accept() {
    Settings        s;

    s.interval = m_common.timeout->text().toInt();

    s.view.buzz_int = m_view.buzz_int->text().toInt();
    s.view.buzz_dev = m_view.buzz_dev->text().toInt();

    s.pie.border  = m_pie.border->text();
    s.pie.filling = m_pie.filling->text();

    //
    // Do not trust double validators
    //

    qreal op_normal  = m_view.op_normal->text().toDouble();
    qreal op_focused = m_view.op_focused->text().toDouble();

    if(op_normal < 0.0 || op_normal > 1.0) {
        QMessageBox::warning(this, "Validation error", "View opacity must lie within 0.0 and 1.0");
        m_view.op_normal->setFocus();
        return;
    }

    if(op_focused < 0.0 || op_focused > 1.0) {
        QMessageBox::warning(this, "Validation error", "View opacity must lie within 0.0 and 1.0");
        m_view.op_focused->setFocus();
        return;
    }

    s.view.op_normal  = op_normal;
    s.view.op_focused = op_focused;

    accept();
}
