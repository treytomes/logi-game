#ifndef __I18N_H__
#define __I18N_H__

#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

#endif
