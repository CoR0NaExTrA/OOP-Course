chcp 65001 > nul
@echo off

SET MyProgram="%~1"

if "%~1"=="" (
    echo Please specify path to program
    exit /B 1
)

REM Find text in empty file
%MyProgram% "%~dp0Empty.txt" "Очумелов" | findstr /x /c:"Text not found" || goto err
echo Test 1 passed

REM Ищем строку в обычном файле
%MyProgram% "%~dp0Text.txt" "Очумелов" > "%~dp0Actual.txt" || goto err
fc "%~dp0Result1.txt" "%~dp0Actual.txt" || goto err
echo Test 2 passed

REM Тесты прошли успешно
echo All tests passed successfully
exit /B 0

REM Если произойдет ошибка
:err
echo Test failed
exit /B 1
