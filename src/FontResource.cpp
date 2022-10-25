#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <iostream>

#include <libintl.h>
#include <locale.h>
#define _(STRING) gettext(STRING)

#include "FontResource.h"

#define JSON_USE_IMPLICIT_CONVERSIONS 0
#include "json.hpp"
using json = nlohmann::json;

void FontResource::load() {
	ifstream f(getPath());
	if (!f.good()) {
		cerr << _("Unable to open file: ") << getPath() << endl;
	} else {
		json data = json::parse(f);
		string file = data["file"].get<string>();
		int pointSize = data["pointSize"].get<int>();

		cout << "Font path: " << file << endl;
		cout << "Point size: " << pointSize << endl;
		TTF_Font* font = TTF_OpenFont(file.c_str(), pointSize);
		if (!font) {
			cerr << _("Error loading font: ") << TTF_GetError() << endl;
		}
		setValue(font);
	}
}

void FontResource::unload() {
	TTF_CloseFont(getValue());
}
