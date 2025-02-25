SET MyProgram = "%~1"

REM ѕустой ввод в консоли
%MyProgram% > "%TEMP%\output.txt%" || goto err
fc "“екст.txt" "%TEMP%\output.txt%" || goto err

REM ќбычный ввод в консоль
%MyProgram% "16" "10" "1F" > "%TEMP%\output.txt%" || goto err
fc "1F.txt" "%TEMP%\output.txt%" || goto err

REM ¬вод INT_MAX в консоль
%MyProgram% "16" "10" "2147483647" > "%TEMP%\output.txt%" || goto err
fc "INT_MAX.txt" "%TEMP%\output.txt%" || goto err

REM ¬вод INT_MIN в консоль
%MyProgram% "16" "10" "-2147483648" > "%TEMP%\output.txt%" || goto err
fc "INT_MIN.txt" "%TEMP%\output.txt%" || goto err

REM ¬вод -1 в значении
%MyProgram% "16" "10" "-1" > "%TEMP%\output.txt%" || goto err
fc "INT_MIN.txt" "%TEMP%\output.txt%" || goto err

REM ¬вод не числа вместо значени€ если не перва€ система не подразумевает буквенных обозначений
%MyProgram% "10" "02" "A" > "%TEMP%\output.txt%" || goto err
fc "Pam.txt" "%TEMP%\output.txt%" || goto err

REM ¬вод не числа вместо 1-ого или 2-ого параметра
%MyProgram% "16" "a" "1F" > "%TEMP%\output.txt%" || goto err
fc "stoi.txt" "%TEMP%\output.txt%" || goto err

REM ¬вод 1-ого и 2-ого параметра больше 36 или меньше 2
%MyProgram% "16" "37" "1F" > "%TEMP%\output.txt%" || goto err
fc "Radix.txt" "%TEMP%\output.txt%" || goto err

echo All tests passed successfully
exit B /0

:err
echo Tests failed
exit B /1