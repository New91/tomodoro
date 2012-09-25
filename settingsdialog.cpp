#include "settingsdialog.h"



#include <QBoxLayout>

#include <QDialogButtonBox>

SettingsDialog::SettingsDialog(QWidget *parent) :
    QDialog(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

    ////

    QBoxLayout*    main_layout = new QVBoxLayout;

    QDialogButtonBox*    button_box =
            new QDialogButtonBox(QDialogButtonBox::Save | QDialogButtonBox::Cancel, Qt::Horizontal, this);

    main_layout->addStretch();

    main_layout->addWidget(button_box);

    setLayout(main_layout);

    connect(button_box, SIGNAL(accepted()), SLOT(accept()));
    connect(button_box, SIGNAL(rejected()), SLOT(reject()));
}


void SettingsDialog::on_accept() {
}
