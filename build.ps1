if (Test-Path build) {
    Remove-Item -Recurse -Force build
}
New-Item -ItemType Directory build
Set-Location build
cmake -G "MinGW Makefiles" ..
cmake --build . --config Debug