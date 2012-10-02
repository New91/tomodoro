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


#include "timer.h"


#include <QApplication>



#include "settings.h"
#include "settingsdialog.h"
#include "pieview.h"
#include "barview.h"

Timer::Timer(QObject *parent) :
    QObject(parent),

    m_timer(),
    m_menu(),
    m_icon(),
    m_parent_holder(),

    m_stop_time(),

    act_start(NULL),
    act_stop(NULL),
    act_switch(NULL),

    m_counter(0),
    m_total(10),

    m_buzz_interval(30),

    m_view_num(0),

    m_settings(NULL),
    m_view(NULL)
{
    // set up the timer
    connect(&m_timer, SIGNAL(timeout()), SLOT(timeout()));

    // set up a menu
    act_start   = m_menu.addAction("Start");
    act_stop    = m_menu.addAction("Cancel");
    act_switch  = m_menu.addAction("Switch view");

    connect(act_start,  SIGNAL(triggered()), SLOT(action_start()));
    connect(act_stop,   SIGNAL(triggered()), SLOT(action_stop()) );
    connect(act_switch, SIGNAL(triggered()), SLOT(action_switch()) );

    connect(m_menu.addAction("Configure"), SIGNAL(triggered()), SLOT(action_configure()));

    connect(m_menu.addAction("Exit"), SIGNAL(triggered()), SLOT(action_exit()));

    show_hide_actions();


    // set up systray icon
    m_icon.setIcon(QIcon(":/resources/tomato.png"));
    m_icon.setContextMenu(&m_menu);
    m_icon.show();

    set_tray_tip();

    m_view_num = Settings().default_view;


    // read settings
    update_settings();
}

void Timer::show_hide_actions() {
    const bool idle = (m_view == NULL);

    act_start ->setVisible( idle);
    act_stop  ->setVisible(!idle);
    act_switch->setVisible(!idle);
}

void Timer::create_new_view() {
    if(m_view != NULL) {
        delete m_view;
    }

    if ((m_view_num & 1) == 0) {
        m_view = new PieView(&m_parent_holder);
    }else{
        m_view = new BarView(&m_parent_holder);
    }

    //connect(this, SIGNAL(tick(int,int)), m_view, SLOT(tick(int,int)));
    connect(m_view, SIGNAL(customContextMenuRequested(QPoint)), SLOT(view_context_request(QPoint)));

    // show a view
    m_view->show();

    m_view->tick(m_counter, m_total);
}


void Timer::timeout() {
    if(m_view != NULL) {
        if(m_counter < m_total) {
            m_counter++;
        } else {
            m_timer.setInterval(m_buzz_interval);
        }

        /* emit */ m_view->tick(m_counter, m_total);
    }else if (!m_stop_time.isNull()) {
        // If we're not counting anything (we have no view),
        // update the icon's tooltip to indicate idle time.

        int elapsed_sec = m_stop_time.elapsed() / 1000;

        QString tip = QString("idling for %1:%2")
                 .arg(QString::number(elapsed_sec / 60), 2, '0')
                 .arg(QString::number(elapsed_sec % 60), 2, '0');

        set_tray_tip(tip);
    }
}



void Timer::action_start(){
    // reset the timer
    m_counter = 0;
    m_timer.start(1000);

    create_new_view();

    show_hide_actions();

    set_tray_tip();
}

void Timer::action_stop() {
    delete m_view;
    m_view = NULL;

    show_hide_actions();

    // stop the timer
    m_timer.start(1000);

    // memorize current time
    m_stop_time.start();
}

void Timer::action_switch() {
    m_view_num++;

    create_new_view();
}

void Timer::action_configure() {
    if(m_settings == NULL) {
        m_settings = new SettingsDialog;

        connect(m_settings, SIGNAL(settingsApplied()), SLOT(update_settings()));
        connect(m_settings, SIGNAL(destroyed()), SLOT(dialog_destroyed()));

        m_settings->show();
    }

    m_settings->raise();
    m_settings->activateWindow();
}

void Timer::action_exit() {
    QApplication::exit();
}


void Timer::view_context_request(QPoint local_pos) {
    m_menu.popup( m_view->mapToGlobal(local_pos) );     // NOTE: technically, m_view may be NULL, but that's unlikely
}

void Timer::dialog_destroyed(){
    m_settings = NULL;
}

void Timer::update_settings() {
    qDebug("updating settings");

    Settings    s;

    int new_total = s.interval * 60;
    m_counter = m_counter * new_total / m_total;
    m_total = new_total;

    m_buzz_interval = s.view.buzz_int;

    //m_view_num = s.default_view;

    if(m_view != NULL) {
        m_view->update_settings();
    }
}
