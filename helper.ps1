# Delete object files and the DLL file, then remove the build directory
Remove-Item -Path "src\*.o" -Force
Remove-Item "build\mps-helper.dll"
Remove-Item -Recurse -Force build