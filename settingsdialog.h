#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>

#include "settings.h"


class QLineEdit;
class QComboBox;

class SettingsDialog : public QDialog
{
    Q_OBJECT


private:
    struct {
        QLineEdit*      timeout;
    } m_common;

    struct {
        QLineEdit*      op_normal;
        QLineEdit*      op_focused;

        QLineEdit*      buzz_int;
        QLineEdit*      buzz_dev;
    } m_view;

    struct {
        QLineEdit*      radius;
        QLineEdit*      text_size;

#define PIE_COLOR(name, member)     QLineEdit* member;
        PIE_COLORS
#undef PIE_COLOR

        QComboBox*      direction1;
        QComboBox*      direction2;
        QComboBox*      inverted;
    } m_pie;




    void load_configuration();

private slots:
    void on_accept();
    
public:
    explicit SettingsDialog(QWidget *parent = 0);

};

#endif // SETTINGSDIALOG_H
