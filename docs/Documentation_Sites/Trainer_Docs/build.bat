copy "..\..\..\src\data\battle_partners.party" "./"
copy  "..\..\..\src\data\trainers.party" "./"

py SortParty.py
del trainers.party
rename trainers_sorted.party trainers.party

py main.py
py createsitefromindx.py
