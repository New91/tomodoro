#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QWidget>


//
// Some cool useful macros
//


#define SETTING_NAMES   \
    SETTING_NAME(interval);     \
    SETTING_NAME(op_normal);    \
    SETTING_NAME(op_focused);   \
    SETTING_NAME(buzz_int);     \
    SETTING_NAME(buzz_dev);     \
    SETTING_NAME(text_size);    \
    SETTING_NAME(main_dir);     \
    SETTING_NAME(inverted);     \
    SETTING_NAME(border);       \
    SETTING_NAME(filling);      \
    SETTING_NAME(text_border);  \
    SETTING_NAME(text_filling); \
    SETTING_NAME(text_color);   \
    SETTING_NAME(pie_radius);   \
    SETTING_NAME(pie_grow_dir); \
    SETTING_NAME(bar_length);   \
    SETTING_NAME(bar_width);





#define VIEW_COLORS      \
    VIEW_COLOR("Border",        border);        \
    VIEW_COLOR("Filling",       filling);       \
    VIEW_COLOR("Text",          text_color);    \
    VIEW_COLOR("Text border",   text_border);   \
    VIEW_COLOR("Text filling",  text_filling);



class Settings : public QObject
{
    Q_OBJECT

private:

#define SETTING_NAME(name)  static const char  name_ ## name[];
    SETTING_NAMES
#undef SETTING_NAME


public:
    explicit Settings(QObject *parent = 0) : QObject(parent) {
    }

    template<const char* name>
    class StrRef {
    public:
        operator QString() const {
            return QSettings().value(name, "").toString();
        }

        StrRef& operator = (QString i) {
            QSettings().setValue(name, i);
            return *this;
        }
    };

    template<const char* name, int deflt = 0>
    class IntRef {
    public:
        operator int() const {
            return QSettings().value(name, deflt).toInt();
        }

        IntRef& operator = (int i) {
            QSettings().setValue(name, i);
            return *this;
        }
    };

    template<const char* name, int deflt_nom = 0, int deflt_denom = 1>
    class RealRef {
    public:
        operator qreal() const {
            return QSettings().value(name, static_cast<qreal>(deflt_nom) / deflt_denom).toReal();
        }

        RealRef& operator = (qreal v) {
            QSettings().setValue(name, v);
            return *this;
        }
    };

    /////

    QColor defaultToText(const QWidget* w, QColor c) const {
        return c.isValid() ? c : w->palette().text().color();
    }

    QColor defaultToButton(const QWidget* w, QColor c) const {
        return c.isValid() ? c : w->palette().button().color();
    }

    ///////

    IntRef<name_interval, 25 * 60>          interval;

    struct {
        RealRef<name_op_normal,  5, 10>     op_normal;
        RealRef<name_op_focused, 8, 10>     op_focused;

        IntRef<name_buzz_int, 30>           buzz_int;
        IntRef<name_buzz_dev, 5>            buzz_dev;

        IntRef<name_text_size, 12>          text_size;

        IntRef<name_main_dir, 0>            main_dir;       // main direction (0 - top, 1 - right, 2 - bottom, 3 - left)
        IntRef<name_inverted, 0>            inverted;       // waxing (0) or waning (1)

        StrRef<name_border>                 border;
        StrRef<name_filling>                filling;
        StrRef<name_text_border>            text_border;
        StrRef<name_text_filling>           text_filling;
        StrRef<name_text_color>             text_color;
    } view;

    struct {
        IntRef<name_pie_radius, 100>        radius;

        IntRef<name_pie_grow_dir, 0>        grow_dir;       // clockwise (1) or counterclockwise (0)
    } pie;

    struct {
        IntRef<name_bar_length, 100>        length;
        IntRef<name_bar_width, 20>          width;
    } bar;
};

#endif // SETTINGS_H
