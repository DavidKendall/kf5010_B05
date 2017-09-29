# curses-jynx
Curses examples and curses simulator of lcd panel as if on the ARM boards

# Dependency
This builds againt the wide-character version of curses (ncursesw).  You will need the library _and_ the development headers.
Version 5 seems to be the current version in package repositories.

```bash
apt install libncursesw5 libncursesw5-dev
```

# Files

* Makefile
  The build configuration for the library and examples
* lcd.h
  The header file defining the interface for the LCD api
* lcd.c
  The source for the library
* lcd.3
  The man page 
  
