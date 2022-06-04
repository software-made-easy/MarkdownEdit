![Made with C++](https://forthebadge.com/images/badges/made-with-c-plus-plus.svg)
[![Powered by Qt](https://forthebadge.com/images/badges/powered-by-qt.svg)](https://qt.io)
[![CodeFactor](https://www.codefactor.io/repository/github/software-made-easy/markdownedit/badge/main)](https://www.codefactor.io/repository/github/software-made-easy/markdownedit/overview/main)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0)
[![GitHub release](https://img.shields.io/github/release/software-made-easy/MarkdownEdit.svg)](https://github.com/software-made-easy/MarkdownEdit/releases/)


# MarkdownEdit

MarkdownEdit, as the name suggests, is a simple and easy program for creating and editing Markdown files.

-------

## Features:

- Spell checker
- Save and load Markdown files
- Undo-Redo
- Preview Markdown files in real time (<1 ms)
- Syntax highlighting editor
- Auto-complete (close brackets, list, ...)
- Find/Replace(Ctrl+F/Ctrl+R)
- Export to HTML
- Bad in resources
- Quick opening of recent files (Button in toolbar or in the file menu)
- Open source
- Native look and feel
- Remember spelling language for every document

![Example](doc/images/Example.png)

## Dependencies:
[Qt](https://qt.io/) and [enchant-2](https://github.com/AbiWord/enchant).

## Note(s):
- To improve performance when using images, disable the "Auto add file path to icon path" option (menu <u>V</u>iew).
- When building with CMake, the translations will **not** work!


-------

## Build instructions
Run the [build script](scripts/build.sh) or follow the instructions below.

- Clone MarkdownEdit: `git clone https://github.com/software-made-easy/MarkdownEdit && cd MarkdownEdit`
- Clone all repositories required by MarkdownEdit by running the command `git submodule update --init --recursive -j 3`.
- Create the build folder: `mkdir build && cd build`.
- Now create a Makefile with CMake: `cmake ..` or qmake (recommended): `qmake ..`
- Run make: `make -j4`

In summary:
```bash
git clone https://github.com/software-made-easy/MarkdownEdit && cd MarkdownEdit
git submodule update --init --recursive -j 3
mkdir build && cd build
qmake ..
make -j4
```

## Credits

- The conversion from Markdown to HTML is done with the help of the [md4c](https://github.com/mity/md4c) - library by *Martin Mitáš*.
- The [widget](https://github.com/pbek/qmarkdowntextedit) used for writing was created by *Patrizio Bekerle*.
