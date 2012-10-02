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


#ifndef TIMER_H
#define TIMER_H

#include <QTime>
#include <QTimer>
#include <QMenu>
#include <QSystemTrayIcon>


class SettingsDialog;
class AbstractView;

class Timer : public QObject
{
    Q_OBJECT

private:

    QTimer              m_timer;
    QMenu               m_menu;
    QSystemTrayIcon     m_icon;
    QWidget             m_parent_holder;

    QTime               m_stop_time;

    QAction*            act_start;
    QAction*            act_stop;
    QAction*            act_switch;

    int                 m_counter;
    int                 m_total;

    int                 m_buzz_interval;

    int                 m_view_num;

    SettingsDialog*     m_settings;
    AbstractView*       m_view;

    void show_hide_actions();

    void create_new_view();

    void set_tray_tip(QString m = QString()) {
        if(m.isNull()) {
            m_icon.setToolTip("Tomodoro");
            return;
        }

        m_icon.setToolTip(QString("Tomodoro (%1)").arg(m));
    }

private slots:
    // timer timeout
    void timeout();

    // action handlers
    void action_start();
    void action_stop();
    void action_switch();
    void action_configure();
    void action_exit();

    // right-click handler for the view
    void view_context_request(QPoint);

    // dialog handlers
    void dialog_destroyed();
    void update_settings();

public:
    explicit Timer(QObject *parent = 0);
    
signals:
    // void tick(int current, int total);

public slots:
    
};

#endif // TIMER_H
