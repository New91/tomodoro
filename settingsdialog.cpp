#include "settingsdialog.h"


#include "colorselector.h"

#include <QMessageBox>

#include <QBoxLayout>
#include <QFormLayout>

#include <QTabWidget>
#include <QGroupBox>
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

    QBoxLayout*         main_layout = new QVBoxLayout(this);

    {
        QGroupBox*      gr   = new QGroupBox("General");
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

        form->addRow("&Radius (px)",     m_pie.radius = new QLineEdit);
        form->addRow("&Font size (px)",  m_pie.text_size = new QLineEdit);

        m_pie.radius->setValidator(new QIntValidator(10, 1000, this));
        m_pie.text_size->setValidator(new QIntValidator(5, 30, this));

#define PIE_COLOR(name, member)                            \
        {                                                       \
            ColorSelector*  sel = new ColorSelector;            \
            QBoxLayout*     l = new QHBoxLayout;                \
            l->addWidget(m_pie.member = sel->attachedEdit());   \
            l->addWidget(sel);                                  \
            form->addRow(name, l);                              \
        }

        PIE_COLORS;

#undef PIE_COLOR

        form->addRow("Start &direction", m_pie.direction1 = new QComboBox);
        form->addRow("Grown d&irection", m_pie.direction2 = new QComboBox);
        form->addRow("&Behaviour", m_pie.inverted = new QComboBox);

        m_pie.direction1->addItem("Top");
        m_pie.direction1->addItem("Right");
        m_pie.direction1->addItem("Bottom");
        m_pie.direction1->addItem("Left");

        m_pie.direction2->addItem("Counterclockwise");
        m_pie.direction2->addItem("Clockwise");

        m_pie.inverted->addItem("Waxing");
        m_pie.inverted->addItem("Waning");

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

    m_pie.radius->setText(QString::number(s.pie.radius));
    m_pie.text_size->setText(QString::number(s.pie.text_size));

#define PIE_COLOR(name, member) m_pie.member->setText(s.pie.member);
    PIE_COLORS;
#undef PIE_COLOR

    m_pie.direction1->setCurrentIndex(s.pie.direction1);
    m_pie.direction2->setCurrentIndex(s.pie.direction2);
    m_pie.inverted  ->setCurrentIndex(s.pie.inverted);
}

void SettingsDialog::on_accept() {
    Settings        s;

    s.interval = m_common.timeout->text().toInt();

    s.view.buzz_int = m_view.buzz_int->text().toInt();
    s.view.buzz_dev = m_view.buzz_dev->text().toInt();

    s.pie.radius    = m_pie.radius->text().toInt();
    s.pie.text_size = m_pie.text_size->text().toInt();

#define PIE_COLOR(name, member) s.pie.member = m_pie.member->text();
    PIE_COLORS;
#undef PIE_COLOR

    s.pie.direction1 = m_pie.direction1->currentIndex();
    s.pie.direction2 = m_pie.direction2->currentIndex();
    s.pie.inverted   = m_pie.inverted  ->currentIndex();

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
