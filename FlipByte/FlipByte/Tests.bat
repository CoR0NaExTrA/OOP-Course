@echo off

SET MyProgram = "%~1"

REM ¬ аргументах не подаетс€ числа
%MyProgram% findstr /x /c:"Error: Enter a single number as an argument." || goto err
echo Test 1 passed

REM ¬ аргументах подано обычное число, не выход€щее за пределы


REM ¬ аргументах подано число, выход€щее за пределы 8-битного числа


REM ¬ аргументах подано не число


REM ¬ аргументах подано число в другой системе счислени€


echo Tests passed successfully
exit /B 0

:err
echo Tests failed
exit /B 1