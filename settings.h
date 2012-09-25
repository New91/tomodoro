#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>

class Settings : public QObject
{
    Q_OBJECT

private:
    static const char  name_interval[];

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

    IntRef<name_interval, 25 * 60>      interval;

};

#endif // SETTINGS_H
