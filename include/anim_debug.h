#pragma once
#include "global.h"

#ifdef DEBUG_ANIM
#include "task.h"

#include "sprite.h"
#include "sound.h"

static inline bool8 AnimDbg_MGBAOpen(void) {
    #if !defined(NDEBUG)
    return TRUE;
    #else
    return FALSE;
    #endif
}

#define ANIMDBG(fmt, ...)                                                     \
    do {                                                                      \
            MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] " fmt, ##__VA_ARGS__);        \
    } while (0)

// Dumpa tutti gli sprite "inUse".
void AnimDbg_DumpSprites(const char *tag);

// Helper: verifica che uno spriteId sia valido/visibile.
bool8 AnimDbg_CheckSpriteValid(u8 spriteId, const char *who);

// Live-tracking delle Visual Task (quelle contate da gAnimVisualTaskCount)
void AnimDbg_VTaskOnCreate(u8 taskId, TaskFunc func);
void AnimDbg_VTaskOnDestroy(u8 taskId);
void AnimDbg_DumpVisualTasks(const char *tag);
void AnimDbg_DumpAffineMatrixUsage(const char *tag);
void AnimDbg_MatDumpIfShared(u8 spr, const char *tag);

#else  // !DEBUG_ANIM

#define ANIMDBG(...) do {} while (0)
static inline void AnimDbg_DumpSprites(const char *tag) {(void)tag;}
static inline bool8 AnimDbg_CheckSpriteValid(u8 spriteId, const char *who) {
    (void)spriteId; (void)who; return TRUE;
}

#endif // DEBUG_ANIM
