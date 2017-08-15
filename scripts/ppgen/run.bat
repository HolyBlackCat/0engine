g++ ppgen.cpp -o ppgen.exe -std=c++17 -Wall -Wextra -pedantic-errors
pause
ppgen.exe
del /F /Q ppgen.exe
g++ preprocessor.h -std=c++17 -Wall -Wextra -pedantic-errors -fsyntax-only
pause
move /Y preprocessor.h ../../src
