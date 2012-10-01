#ifndef CUSTOMLABEL_H
#define CUSTOMLABEL_H

#include <QWidget>

class CustomLabel : public QWidget
{
    Q_OBJECT

private:

    QString         m_text;

    QSize           m_size_hint;

    int             m_font_size;

    struct {
        QColor      bkg;
        QColor      border;
        QColor      text;
    } m_colors;

protected:
    void paintEvent ( QPaintEvent * event );

//public:
    QSize sizeHint() const;

public:
    explicit CustomLabel(QWidget *parent = 0);

public slots:
    void setText ( const QString & );
    void update_settings();
};

#endif // CUSTOMLABEL_H
