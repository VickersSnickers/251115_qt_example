@echo off
setlocal

set BUILD_TYPE=Ninja
set BUILD_FOLDER=build
set SOURCE_FOLDER=.
set IMG_FOLDER=img

REM
if not exist "%BUILD_FOLDER%" (
    mkdir "%BUILD_FOLDER%"
)

cd "%BUILD_FOLDER%"

REM
cmake -G "%BUILD_TYPE%" "..\%SOURCE_FOLDER%"
cmake --build .

REM
if not exist "%IMG_FOLDER%" (
    mkdir "%IMG_FOLDER%"
)

copy "..\%IMG_FOLDER%\grustnii-smail.png" "%IMG_FOLDER%\" >nul

cd ..
endlocal
