#include "settings.h"

#define SETTING_NAME(name)      \
    const char  Settings::name_ ## name[] = #name

SETTING_NAME(interval);

// view
SETTING_NAME(op_normal);
SETTING_NAME(op_focused);
SETTING_NAME(buzz_int);
SETTING_NAME(buzz_dev);


// pie
SETTING_NAME(pie_radius);
SETTING_NAME(pie_text_size);
SETTING_NAME(pie_border);
SETTING_NAME(pie_filling);
SETTING_NAME(pie_text_border);
SETTING_NAME(pie_text_filling);
SETTING_NAME(pie_text_color);


#undef SETTING_NAME
