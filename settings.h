#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

#include <QDebug>

class Settings : public QObject
{
    Q_OBJECT

private:
    static const char  name_interval[];
    static const char  name_op_normal[];
    static const char  name_op_focused[];
    static const char  name_buzz_int[];
    static const char  name_buzz_dev[];

public:
    explicit Settings(QObject *parent = 0) : QObject(parent) {
    }

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

    IntRef<name_interval, 25 * 60>      interval;

    struct {
        RealRef<name_op_normal,  5, 10>     op_normal;
        RealRef<name_op_focused, 8, 10>     op_focused;

        IntRef<name_buzz_int, 30>           buzz_int;
        IntRef<name_buzz_dev, 5>            buzz_dev;
    } view;
};

#endif // SETTINGS_H
