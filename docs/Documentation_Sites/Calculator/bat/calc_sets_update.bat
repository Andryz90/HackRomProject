@echo generating gen9.js from Trainer Docs

rem .\ gen9.js @echo Removing old .js

@echo Generating new one

pushd ..\..\Trainer_Docs\

call build.bat 2>&1 | powershell -NoProfile -Command ^
  "$input | ForEach-Object { Write-Host $_ -ForegroundColor Magenta }"

popd

python .\calc_sets_modifier.py
move gen9.js ..\src\js\data\sets\gen9.js
