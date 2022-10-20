# logi-game

Logstics/logic circuit simulation game.

## Internationalization

Internationalization is handled by gettext.

To generate logi-game.pot:
`xgettext --keyword=_ --language=C++ --add-comments --sort-output -o locale/logi-game.pot src/main.cpp`

To generate a language file (English in this case):
`msginit --input=locale/logi-game.pot --locale=en --output=locale/en/logi-game.po`

To compile the .mo file (also handled by the Makefile):
`msgfmt --output-file=locale/en/LC_MESSAGES/logi-game.mo locale/en/logi-game.po`

When new strings are added to the source, re-generate the pot file and merge the new strings into the language files:
`msgmerge --update locale/en/logi-game.po locale/logi-game.pot`

Learned to do this from the tutorial [here](https://www.labri.fr/perso/fleury/posts/programming/a-quick-gettext-tutorial.html).

## Dependencies

* SDL2
* SDL2_ttf
* SDL2_image
* https://github.com/nlohmann/json
    * Provides json.hpp.
    * [Documentation.](https://json.nlohmann.me/)
* [Ubuntu Mono font family.](https://fonts.google.com/specimen/Ubuntu+Mono)
    * [License](https://ubuntu.com/legal/font-licence)
* [Bootstrap Icons v1.9.1](https://github.com/twbs/icons/releases/tag/v1.9.1)
    * [Index](https://icons.getbootstrap.com/)
    * Changed all colors from `currentColor` to `white`.
* [gettext 0.21](https://www.gnu.org/software/gettext/)
* ~[Boost 1.74.0](https://www.boost.org/doc/libs/1_74_0)~
