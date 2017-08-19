g++ mathgen.cpp -o mathgen.exe -std=c++17 -Wall -Wextra -pedantic-errors
pause
mathgen.exe
del /F /Q mathgen.exe
g++ extended_math.h -std=c++17 -Wall -Wextra -pedantic-errors -fsyntax-only
pause
move /Y extended_math.h ../../src