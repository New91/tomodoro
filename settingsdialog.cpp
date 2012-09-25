#include "settingsdialog.h"


#include "settings.h"


#include <QMessageBox>

#include <QBoxLayout>
#include <QFormLayout>

#include <QGroupBox>
#include <QDialogButtonBox>

#include <QLineEdit>

#include <QIntValidator>
#include <QDoubleValidator>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ////

    QBoxLayout*         main_layout = new QVBoxLayout(this);

    // common group

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
}

void SettingsDialog::on_accept() {
    Settings        s;

    s.interval = m_common.timeout->text().toInt();

    s.view.buzz_int = m_view.buzz_int->text().toInt();
    s.view.buzz_dev = m_view.buzz_dev->text().toInt();

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
