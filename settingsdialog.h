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

        QComboBox*      default_view;
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

    struct {
        QLineEdit*      length;
        QLineEdit*      width;
    } m_bar;




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
