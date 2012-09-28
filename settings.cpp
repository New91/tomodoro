#include "settings.h"

#define SETTING_NAME(name)      \
    const char  Settings::name_ ## name[] = #name

SETTING_NAMES

#undef SETTING_NAME
