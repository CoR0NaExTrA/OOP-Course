SET MyProgram = "%~1"

REM Чтение матрицы из консоли
%MyProgram% "1 \t 2 \t 3\n 0 \t 1 \t 4\n 5\t 6\t 0" > "%TEMP%\output.txt" || goto err
fc "Result.txt" "%TEMP%\output.txt" || goto err

REM Чтение матрицы из файла
%MyProgram% "matrix.txt" > "%TEMP%\output.txt" || goto err
fc "Result.txt" "%TEMP%\output.txt" || goto err

REM Чтение матрицы которая не может иметь обратной и вывод ошибки
%MyProgram% "Non-invertible.txt" > "%TEMP%\output.txt" || goto err
fc "Result2.txt" "%TEMP%\output.txt" || goto err

REM Чтение матрицы с ошибкой в ней
%MyProgram% "InvalidMatrix.txt" > "%TEMP%\output.txt" || goto err
fc "Result3.txt" "%TEMP%\output.txt" || goto err

REM Чтение параметра -h для выдачи информации о своём использовании
%MyProgram% "-h" > "%TEMP%\output.txt" || goto err
fc "Result4.txt" "%TEMP%\output.txt" || goto err

REM Чтение матрицы которая не является квадратной порядка 3
%MyProgram% "InvalidFormat.txt" > "%TEMP%\output.txt" || goto err
fc "Result5.txt" "%TEMP%\output.txt" || goto err

echo All tests passed successfully
exit B /0

:err
echo Tests failed
exit B /1