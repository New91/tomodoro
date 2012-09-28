#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>


//
// Some cool useful macros
//


#define SETTING_NAMES   \
    SETTING_NAME(interval);             \
    SETTING_NAME(op_normal);            \
    SETTING_NAME(op_focused);           \
    SETTING_NAME(buzz_int);             \
    SETTING_NAME(buzz_dev);             \
    SETTING_NAME(pie_radius);           \
    SETTING_NAME(pie_text_size);        \
    SETTING_NAME(pie_direction1);       \
    SETTING_NAME(pie_direction2);       \
    SETTING_NAME(pie_inverted);         \
    SETTING_NAME(pie_border);           \
    SETTING_NAME(pie_filling);          \
    SETTING_NAME(pie_text_border);      \
    SETTING_NAME(pie_text_filling);     \
    SETTING_NAME(pie_text_color);






#define PIE_COLORS      \
    PIE_COLOR("Border",        border);        \
    PIE_COLOR("Filling",       filling);       \
    PIE_COLOR("Text",          text_color);    \
    PIE_COLOR("Text border",   text_border);   \
    PIE_COLOR("Text filling",  text_filling);



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

    IntRef<name_interval, 25 * 60>          interval;

    struct {
        RealRef<name_op_normal,  5, 10>     op_normal;
        RealRef<name_op_focused, 8, 10>     op_focused;

        IntRef<name_buzz_int, 30>           buzz_int;
        IntRef<name_buzz_dev, 5>            buzz_dev;
    } view;

    struct {
        IntRef<name_pie_radius, 100>        radius;
        IntRef<name_pie_text_size, 12>      text_size;

        IntRef<name_pie_direction1, 0>      direction1;     // start direction (0 - top, 1 - right, 2 - bottom, 3 - left)
        IntRef<name_pie_direction2, 0>      direction2;     // clockwise (1) or counterclockwise (0)
        IntRef<name_pie_inverted, 0>        inverted;       // gradually waxes (0) or wanes (1)

        StrRef<name_pie_border>             border;
        StrRef<name_pie_filling>            filling;
        StrRef<name_pie_text_border>        text_border;
        StrRef<name_pie_text_filling>       text_filling;
        StrRef<name_pie_text_color>         text_color;
    } pie;
};

#endif // SETTINGS_H
