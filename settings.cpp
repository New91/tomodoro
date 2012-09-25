#include "settings.h"

#define SETTING_NAME(name)      \
    const char  Settings::name[] = #name

SETTING_NAME(name_interval);
SETTING_NAME(name_op_normal);
SETTING_NAME(name_op_focused);
SETTING_NAME(name_buzz_int);
SETTING_NAME(name_buzz_dev);



#undef SETTING_NAME
