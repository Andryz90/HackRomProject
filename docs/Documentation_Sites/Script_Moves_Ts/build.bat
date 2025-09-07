del "./*.h"
del "./*.ts"
copy "..\..\..\src\data\moves_info.h" "./"
copy "..\Calculator\calc\src\data\moves.ts" "./"
py update_moves.py
rename moves.ts moves_original.ts
rename moves.ts.updated moves.ts