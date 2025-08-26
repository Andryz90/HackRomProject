@echo off
Copying trainers.party from source...
cp "./src/data/trainers.party" "./"

@echo off
REM Avvia SortParty.py
echo Eseguo SortParty.py...
python SortParty.py
if errorlevel 1 (
    echo SortParty.py ha fallito!
    pause
    exit b 1
)

REM Avvia parse_trainers.py
echo Eseguo parse_trainers.py...
python parse_trainers.py
if errorlevel 1 (
    echo parse_trainers.py ha fallito!
    pause
    exit b 1
)

echo Tutti gli script eseguiti correttamente.
pause
