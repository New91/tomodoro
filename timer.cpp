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
    m_total(100)
{
    // set up the timer
    m_timer.start(1000);

    connect(&m_timer, SIGNAL(timeout()), SLOT(timeout()));



    // set up a menu
    m_menu.addAction("Something");
    m_menu.addSeparator();
    connect(m_menu.addAction("Exit"), SIGNAL(triggered()), SLOT(action_exit()));

    // show a view
    m_view = new PieView(&m_parent_holder);
    m_view->show();

    connect(this, SIGNAL(tick(int,int)), m_view, SLOT(tick(int,int)));

    connect(m_view, SIGNAL(customContextMenuRequested(QPoint)), SLOT(view_context_request(QPoint)));


    // set up systray icon
    m_icon.setIcon(QIcon(":/resources/tomato.png"));
    m_icon.setToolTip("Tomodoro");
    m_icon.setContextMenu(&m_menu);
    m_icon.show();
}


void Timer::timeout() {
    if(m_counter < m_total) m_counter++;

    emit tick(m_counter, m_total);
}


void Timer::action_exit() {
    QApplication::exit();
}


void Timer::view_context_request(QPoint local_pos) {
    m_menu.popup( m_view->mapToGlobal(local_pos) );
}

