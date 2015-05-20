#!/bin/bash
mkdir $1
cd $1
printf 'PROJECT_NAME := %s\ninclude ../build.mk' $1 > makefile
mkdir src
cd src
printf '#include <stdio.h>\n\nint main()\n{\n\n}\n' > $1.cpp
notepad++ $1.cpp &
cd ..