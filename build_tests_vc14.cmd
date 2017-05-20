SET VC_PATH="%VS140COMNTOOLS%\..\..\VC\bin\vcvars32.bat"
SET QT_PATH="D:\Dependency\Qt\5.6\msvc2015"

mkdir build
cd build

call %VC_PATH%
SET PATH=%QT_PATH%\bin;%PATH%

qmake.exe ../tests/tests.pro
nmake
nmake install
pause