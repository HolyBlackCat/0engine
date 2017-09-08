g++ mathgen.cpp -o mathgen.exe -std=c++17 -Wall -Wextra -pedantic-errors
pause
mathgen.exe
del /F /Q mathgen.exe
g++ mat.h -std=c++17 -Wall -Wextra -pedantic-errors -fsyntax-only
pause
move /Y mat.h ../../src