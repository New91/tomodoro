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
        QLineEdit*      text_size;

        QComboBox*      main_dir;
        QComboBox*      inverted;

#define VIEW_COLOR(name, member)     QLineEdit* member;
        VIEW_COLORS
#undef VIEW_COLOR
    } m_view;

    struct {
        QLineEdit*      radius;
        QComboBox*      grow_dir;
    } m_pie;




    void load_configuration();

    bool store_configuration();

private slots:
    void on_accept();
    void on_apply();

public:
    explicit SettingsDialog(QWidget *parent = 0);

signals:
    void settingsApplied();

};

#endif // SETTINGSDIALOG_H
