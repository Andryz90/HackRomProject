#ifndef GUARD_BATTLE_DYNAMAX_H
#define GUARD_BATTLE_DYNAMAX_H

#define DYNAMAX_TURNS_COUNT	       3

#define TUTOR_TYPE_NORMAL       (bool8)(0u)
#define TUTOR_TYPE_MAXMOVE      (bool8)(1u)


bool32 CanDynamax(u32 battler);
bool32 IsGigantamaxed(u32 battler);
void ApplyDynamaxHPMultiplier(struct Pokemon* mon);
void ActivateDynamax(u32 battler);
u16 GetNonDynamaxHP(u32 battler);
u16 GetNonDynamaxMaxHP(u32 battler);
void UndoDynamax(u32 battler);
bool32 IsMoveBlockedByMaxGuard(u32 move);
bool32 IsMoveBlockedByDynamax(u32 move);

u16 GetMaxMove(u32 battler, u32 baseMove);
u32 GetMaxMovePower(u32 move);
bool32 IsMaxMove(u32 move);
void ChooseDamageNonTypesString(u8 type);

void BS_UpdateDynamax(void);
void BS_SetSteelsurge(void);
void BS_HealOneSixth(void);
void BS_TryRecycleBerry(void);
void BS_JumpIfDynamaxed(void);
//Custom
bool8 CanPokemonLearnMaxMove (struct Pokemon* mon);
u16 GetMaxMoveToLearn (void);
bool8 IsTutorMaxMove (void);
void SetTypeTutorMove (bool8 value);
#endif
