Per aggiornare la documentazione:
- Calc: avviare il cmd nella root e avviare "node build" per buildare il progetto, in caso in cui si vogliano aggiornare i sets avviare il .bat nella cartella bat dopo di che avviare npm update @smogon/sets e poi node build per aggiornare il tutto.
- Per generare le moves e le species nuove basta avviare il bat corrispondente nelle cartelle.
- Per aggiornare il Trainer_Docs avviare il build.bat 
- Per aggiornare porydex (fare l'import di tutto): ./.venv/bin/python e poi porydex.py extract oppure ./.venv/bin/python porydex.py extract in WSL nella cartella root.