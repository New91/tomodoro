#ifndef TIMER_H
#define TIMER_H

#include <QTime>
#include <QTimer>
#include <QMenu>
#include <QSystemTrayIcon>


class SettingsDialog;
class PieView;

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

    int                 m_counter;
    int                 m_total;

    int                 m_buzz_interval;


    SettingsDialog*     m_settings;
    PieView*            m_view;

    void show_hide_actions();

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
