@echo off
:-  Clean iBase 1.4c1 and dependent products

:-  Set the IBASE variable to the installation directory
if "%IBASE%"=="" (
    echo The IBASE environment variable is not defined.
    echo Set this to desired installation directory, e.g. c:ibase.
    echo Then, add ^%IBASE^%/bin to your PATH for best results.
    exit /b 1
)

:-  Clean foreign
cd foreign
call boomake clean
if errorlevel 1 (
    echo E: Clean of foreign failed
    exit /b 1
)
cd ..

:-  Clean base1
cd base1
call boomake clean
if errorlevel 1 (
    echo E: Clean of base1 failed
    exit /b 1
)
cd ..

:-  Clean gsl4
cd gsl4
call boomake clean
if errorlevel 1 (
    echo E: Clean of gsl4 failed
    exit /b 1
)
cd ..

:-  Clean base2
cd base2
call boomake clean
if errorlevel 1 (
    echo E: Clean of base2 failed
    exit /b 1
)
cd ..

:-  Done successfully
echo Finished cleaning iBase 1.4c1.

