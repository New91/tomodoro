#ifndef COLORSELECTOR_H
#define COLORSELECTOR_H

#include <QWidget>

class QLineEdit;

class ColorSelector : public QWidget
{
    Q_OBJECT

private:

    //QString         m_string;
    QColor          m_color;

    QLineEdit*      m_attached_edit;

    void set_new_color(QColor n, bool update_edit = true);

protected:
    void paintEvent ( QPaintEvent * event );
    void mouseReleaseEvent ( QMouseEvent * event ) ;
    QSize sizeHint() const ;

private slots:
    void attached_text_changed(QString);
    
public:
    explicit ColorSelector(QWidget *parent = 0);

    QLineEdit*  attachedEdit();

    QColor color() const {
        return m_color;
    }
};

#endif // COLORSELECTOR_H
