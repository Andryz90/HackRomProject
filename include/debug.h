#ifndef GUARD_DEBUG_H
#define GUARD_DEBUG_H

void Debug_ShowMainMenu(void);
void DebugTask_HandleMenuInput_Give(u8 taskId);
void Debug_Custom_Menu (u8 taskId);
extern const u8 Debug_FlagsAndVarNotSetBattleConfigMessage[];

extern EWRAM_DATA bool8 gIsDebugBattle;
extern EWRAM_DATA u32 gDebugAIFlags;

#endif // GUARD_DEBUG_H
