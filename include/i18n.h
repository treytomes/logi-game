#ifndef __I18N_H__
#define __I18N_H__

// TODO: Enable internationalization for Windows.
// https://learn.microsoft.com/en-us/windows/win32/intl/international-support

#ifdef _WIN32
	#define _(STRING) STRING
#else
	#include <libintl.h>
	#include <locale.h>
	#define _(STRING) gettext(STRING)
#endif

#endif
