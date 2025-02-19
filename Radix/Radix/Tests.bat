SET MyProgram = "%~1"

REM Пустой ввод в консоли
%MyProgram% > "%TEMP%\output.txt%" || goto err
fc "Текст.txt" "%TEMP%\output.txt%" || goto err