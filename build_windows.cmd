setlocal enabledelayedexpansion

cd "%~dp0"

set BUILD_DIR=build_win32_qt5

del %BUILD_DIR% /S /Q /F>nul
mkdir %BUILD_DIR%

pushd %BUILD_DIR%
cmake .. -A x64 -DCMAKE_PREFIX_PATH=C:/Qt/5.15/msvc2019_64/lib/cmake
cmake --build . --config Release --target PACKAGE
popd
