@echo off
if -%1 == - goto noparam

cd src
path %path%;%1
call mingw32-make -f Makefile.win BINDIR=%1 DBG="-DDEBUG"
cd ..

goto exit
:noparam
echo This batch file does not need to be run directly.
:exit