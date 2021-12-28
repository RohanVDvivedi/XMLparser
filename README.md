# XMLparser
A C library to build parse tree for XML grammar.

## Setup instructions
**Install dependencies :**
 * [Cutlery](https://github.com/RohanVDvivedi/Cutlery)

**Download source code :**
 * `git clone https://github.com/RohanVDvivedi/XMLparser.git`

**Build from source :**
 * `cd XMLparser`
 * `make clean all`

**Install from the build :**
 * `sudo make install`
 * ***Once you have installed from source, you may discard the build by*** `make clean`

## Using The library
 * add `-lxmlparser -lcutlery` linker flag, while compiling your application
 * do not forget to include appropriate public api headers as and when needed. this includes
   * `#include<xml_parser.h>`
   * `#include<xml_serializer.h>`

## Instructions for uninstalling library

**Uninstall :**
 * `cd XMLparser`
 * `sudo make uninstall`
