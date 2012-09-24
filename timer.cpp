#include "timer.h"


#include <QApplication>




#include "pieview.h"

Timer::Timer(QObject *parent) :
    QObject(parent),
    m_timer(),
    m_menu(),
    m_icon(),
    m_parent_holder(),
    m_counter(0),
    m_total(25*60),
    m_view(NULL)
{
    // set up the timer
    m_timer.start(1000);

    connect(&m_timer, SIGNAL(timeout()), SLOT(timeout()));



    // set up a menu
    act_start = m_menu.addAction("Start");
    act_stop = m_menu.addAction("Cancel");

    connect(act_start, SIGNAL(triggered()), SLOT(action_start()));
    connect(act_stop,  SIGNAL(triggered()), SLOT(action_stop()) );

    m_menu.addSeparator();

    connect(m_menu.addAction("Exit"), SIGNAL(triggered()), SLOT(action_exit()));

    show_hide_actions();


    // set up systray icon
    m_icon.setIcon(QIcon(":/resources/tomato.png"));
    m_icon.setToolTip("Tomodoro");
    m_icon.setContextMenu(&m_menu);
    m_icon.show();
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
            m_timer.setInterval(0.2);
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
}

void Timer::action_stop() {
    //m_view->deleteLater();
    delete m_view;
    m_view = NULL;

    show_hide_actions();
}

void Timer::action_exit() {
    QApplication::exit();
}


void Timer::view_context_request(QPoint local_pos) {
    m_menu.popup( m_view->mapToGlobal(local_pos) );
}

