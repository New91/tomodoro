#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>


class QLineEdit;

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
        QLineEdit*      border;
        QLineEdit*      filling;
    } m_pie;




    void load_configuration();

private slots:
    void on_accept();
    
public:
    explicit SettingsDialog(QWidget *parent = 0);

};

#endif // SETTINGSDIALOG_H
