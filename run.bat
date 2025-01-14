@echo off
setlocal enabledelayedexpansion
set SRC_FILES=

for %%f in (src\*.cpp) do (
    set SRC_FILES=!SRC_FILES! %%f
)

set "PATH=C:\msys64\mingw64\bin\;%PATH%"
C:\msys64\mingw64\bin\gcc.exe -static -LD:/CPPINCLUDE/GLFW/lib -ID:/CPPINCLUDE/GLFW/include -LD:/CPPINCLUDE/GLEW/lib -ID:/CPPINCLUDE/GLEW/include -fdiagnostics-color=always -g -DGLEW_STATIC !SRC_FILES! -o build/main.exe -lglew32s -lopengl32 -lglfw3 -lgdi32 -luser32 -lstdc++
.\build\main.exe
