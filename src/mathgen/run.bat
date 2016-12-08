g++ mathgen.cpp -o mathgen.exe -std=c++14 -Wall -Wextra -pedantic-errors
pause
mathgen.exe
del /F /Q mathgen.exe
g++ math.h -E -o test.txt -std=c++14 -pedantic-errors
del /F /Q test.txt
pause