#ifndef PIEVIEW_H
#define PIEVIEW_H

#include <QPoint>
#include <QWidget>

class PieView : public QWidget
{
    Q_OBJECT


    QPoint      m_anchor;

    int         m_current;
    int         m_total;

protected:
    void paintEvent ( QPaintEvent * event );

    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);

    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);


public:
    explicit PieView(QWidget *parent = 0);
    
signals:
    
public slots:
    void tick(int current, int total);
    
};

#endif // PIEVIEW_H
