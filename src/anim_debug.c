#include "global.h"

#ifdef DEBUG_ANIM
#include "anim_debug.h"
#include "sprite.h"
#include "battle_anim.h"
#include "constants/battle_anim.h"

static bool8     EWRAM_DATA sVTaskAlive[NUM_TASKS] = {0};
static TaskFunc  EWRAM_DATA sVTaskFunc [NUM_TASKS] = {0};

void AnimDbg_VTaskOnCreate(u8 taskId, TaskFunc func)
{
    sVTaskAlive[taskId] = TRUE;
    sVTaskFunc [taskId] = func;
    ANIMDBG("CreateVisualTask id=%u func=%p", taskId, (void*)func);
}

void AnimDbg_VTaskOnDestroy(u8 taskId)
{
    ANIMDBG("DestroyVisualTask id=%u", taskId);
    sVTaskAlive[taskId] = FALSE;
    sVTaskFunc [taskId] = NULL;
}

void AnimDbg_DumpVisualTasks(const char *tag)
{
    MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] ---- VisualTasks dump (%s) ----", tag ? tag : "");
    for (int i = 0; i < NUM_TASKS; i++) {
        if (sVTaskAlive[i]) {
            struct Task *t = &gTasks[i];
            MgbaPrintf(MGBA_LOG_ERROR,
                       "[ANIM] vtask[%02d] func=%p state=%d data:%d,%d,%d,%d,%d,%d",
                       i, (void*)sVTaskFunc[i], t->data[0],
                       t->data[1], t->data[2], t->data[3],
                       t->data[4], t->data[5]);
        }
    }
    MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] ---- end vtask dump ----");
}

void AnimDbg_DumpSprites(const char *tag)
{
    MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] ---- Sprite dump (%s) ----", tag ? tag : "");
    for (int i = 0; i < MAX_SPRITES; i++) {
        const struct Sprite *s = &gSprites[i];
        if (s->inUse) {
            MgbaPrintf(MGBA_LOG_ERROR,
                "[ANIM] spr[%02d] cb=%p x=%3d y=%3d tile=%u pal=%u aff=%u inv=%u "
                "affEnd=%u animEnd=%u mat=%u d0=%d d1=%d d2=%d d3=%d",
                i, (void*)s->callback, s->x, s->y,
                s->oam.tileNum, s->oam.paletteNum, s->oam.affineMode, s->invisible,
                s->affineAnimEnded, s->animEnded, s->oam.matrixNum,
                s->data[0], s->data[1], s->data[2], s->data[3]);
        }
    }
    MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] ---- end dump ----");
}

bool8 AnimDbg_CheckSpriteValid(u8 spriteId, const char *who)
{
    if (spriteId == 0xFF) { // SPRITE_NONE
        ANIMDBG("%s: spriteId=0xFF (SPRITE_NONE) -> invalid", who ? who : "check");
        return FALSE;
    }
    if (spriteId >= MAX_SPRITES) {
        ANIMDBG("%s: spriteId=%u out of range", who ? who : "check", spriteId);
        return FALSE;
    }
    const struct Sprite *s = &gSprites[spriteId];
    if (!s->inUse) {
        ANIMDBG("%s: spriteId=%u not inUse", who ? who : "check", spriteId);
        return FALSE;
    }
    if (s->invisible) {
        ANIMDBG("%s: spriteId=%u invisible", who ? who : "check", spriteId);
        // invisibile non è per forza errore, ma in molte anim è un problema.
    }
    return TRUE;
}

void AnimDbg_DumpAffineMatrixUsage(const char *tag)
{
    u8 cnt[32] = {0};
    for (int i=0;i<MAX_SPRITES;i++) {
        if (!gSprites[i].inUse) continue;
        u8 m = gSprites[i].oam.matrixNum & 0x1F; // 0..31
        if (m <= 31 && (gSprites[i].oam.affineMode != ST_OAM_AFFINE_OFF))
            cnt[m]++;
    }
    MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] -- Matrices (%s) --", tag?tag:"");
    for (int m=0;m<32;m++) if (cnt[m]) {
        MgbaPrintf(MGBA_LOG_ERROR, "mat[%02d] used by %u sprite(s):", m, cnt[m]);
        for (int i=0;i<MAX_SPRITES;i++) {
            if (!gSprites[i].inUse) continue;
            if ((gSprites[i].oam.matrixNum & 0x1F) == m && gSprites[i].oam.affineMode != ST_OAM_AFFINE_OFF) {
                MgbaPrintf(MGBA_LOG_ERROR, "  spr=%02d cb=%p battler=%d",
                    i, (void*)gSprites[i].callback,
                    (i==GetAnimBattlerSpriteId(ANIM_ATTACKER)
                     || i==GetAnimBattlerSpriteId(ANIM_TARGET)
                     || i==GetAnimBattlerSpriteId(ANIM_ATK_PARTNER)
                     || i==GetAnimBattlerSpriteId(ANIM_DEF_PARTNER)));
            }
        }
    }
    MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] -- end --");
}


// Conta quanti sprite usano la stessa matrice del 'spr' dato.
// Se >1, stampa l'elenco (solo quando serve) per non spammare.
void AnimDbg_MatDumpIfShared(u8 spr, const char *tag)
{
    if (spr == 0xFF || !gSprites[spr].inUse) return;
    const u8 mat = gSprites[spr].oam.matrixNum & 0x1F;
    if (gSprites[spr].oam.affineMode == ST_OAM_AFFINE_OFF) return;

    int cnt = 0;
    for (int i = 0; i < MAX_SPRITES; i++)
        if (gSprites[i].inUse &&
            (gSprites[i].oam.matrixNum & 0x1F) == mat &&
            gSprites[i].oam.affineMode != ST_OAM_AFFINE_OFF)
            cnt++;

    if (cnt > 1) {
        MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] mat[%u] SHARED by %d sprites @%s (spr=%u)",
                   mat, cnt, tag ? tag : "", spr);
        for (int i = 0; i < MAX_SPRITES; i++)
            if (gSprites[i].inUse &&
                (gSprites[i].oam.matrixNum & 0x1F) == mat &&
                gSprites[i].oam.affineMode != ST_OAM_AFFINE_OFF)
                MgbaPrintf(MGBA_LOG_ERROR, "  uses: spr=%02d cb=%p", i, (void*)gSprites[i].callback);
    } else {
        MgbaPrintf(MGBA_LOG_ERROR, "[ANIM] mat[%u] solo use @%s (spr=%u)", mat, tag ? tag : "", spr);
    }
}

#endif
