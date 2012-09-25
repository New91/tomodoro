#include "timer.h"


#include <QApplication>



#include "settings.h"
#include "settingsdialog.h"
#include "pieview.h"

Timer::Timer(QObject *parent) :
    QObject(parent),

    m_timer(),
    m_menu(),
    m_icon(),
    m_parent_holder(),

    act_start(NULL),
    act_stop(NULL),

    m_counter(0),
    m_total(10),

    m_settings(NULL),
    m_view(NULL)
{
    // set up the timer
    connect(&m_timer, SIGNAL(timeout()), SLOT(timeout()));

    // set up a menu
    act_start = m_menu.addAction("Start");
    act_stop =  m_menu.addAction("Cancel");

    connect(act_start, SIGNAL(triggered()), SLOT(action_start()));
    connect(act_stop,  SIGNAL(triggered()), SLOT(action_stop()) );

    connect(m_menu.addAction("Configure"), SIGNAL(triggered()), SLOT(action_configure()));

    connect(m_menu.addAction("Exit"), SIGNAL(triggered()), SLOT(action_exit()));

    show_hide_actions();


    // set up systray icon
    m_icon.setIcon(QIcon(":/resources/tomato.png"));
    m_icon.setToolTip("Tomodoro");
    m_icon.setContextMenu(&m_menu);
    m_icon.show();


    // read settings
    update_settings();
}

void Timer::show_hide_actions() {
    if(m_view != NULL) {
        act_start->setVisible(false);
        act_stop ->setVisible(true);
    }else {
        act_start->setVisible(true);
        act_stop->setVisible(false);
    }
}


void Timer::timeout() {
    if(m_view != NULL) {
        if(m_counter < m_total) {
            m_counter++;
        } else {
            m_timer.setInterval(30);
        }

        /* emit */ m_view->tick(m_counter, m_total);
    }
}



void Timer::action_start(){
    // show a view
    m_view = new PieView(&m_parent_holder);
    m_view->show();

    //connect(this, SIGNAL(tick(int,int)), m_view, SLOT(tick(int,int)));
    connect(m_view, SIGNAL(customContextMenuRequested(QPoint)), SLOT(view_context_request(QPoint)));

    show_hide_actions();

    // reset the timer
    m_counter = 0;
    m_timer.start(1000);
}

void Timer::action_stop() {
    delete m_view;
    m_view = NULL;

    show_hide_actions();

    // stop the timer
    m_timer.stop();
}

void Timer::action_configure() {
    if(m_settings == NULL) {
        m_settings = new SettingsDialog;

        connect(m_settings, SIGNAL(accepted()), SLOT(update_settings()));
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
    m_menu.popup( m_view->mapToGlobal(local_pos) );
}

void Timer::dialog_destroyed(){
    m_settings = NULL;
}

void Timer::update_settings() {
    int new_total = Settings().interval;

    m_counter = m_counter * new_total / m_total;
    m_total = new_total;
}
