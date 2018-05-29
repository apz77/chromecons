

IF NOT EXIST "build" mkdir build

IF NOT EXIST "build\*.sln" (
    cmake -H"." -B"build" -G"Visual Studio 14 2015" -T"v140_xp"
) ELSE (
    cmake --build "build" --target "ALL_BUILD" --config "Release"
)