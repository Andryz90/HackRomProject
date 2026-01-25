#ifndef GUARD_FIELD_SPECIALS_H
#define GUARD_FIELD_SPECIALS_H

enum DesertUnderPass_Fossils_t
{
    DESERT_UNDERPASS_HELIX_FOSSIL  = ITEM_HELIX_FOSSIL,
    DESERT_UNDERPASS_DOME_FOSSIL   = ITEM_DOME_FOSSIL,
    DESERT_UNDERPASS_OLD_AMBER     = ITEM_OLD_AMBER,
    DESERT_UNDERPASS_ROOT_FOSSIL   = ITEM_ROOT_FOSSIL,
    DESERT_UNDERPASS_CLAW_FOSSIL   = ITEM_CLAW_FOSSIL,
    DESERT_UNDERPASS_ARMOR_FOSSIL  = ITEM_ARMOR_FOSSIL,
    DESERT_UNDERPASS_SKULL_FOSSIL  = ITEM_SKULL_FOSSIL,
    DESERT_UNDERPASS_COVER_FOSSIL  = ITEM_COVER_FOSSIL,
    DESERT_UNDERPASS_PLUME_FOSSIL  = ITEM_PLUME_FOSSIL,
    DESERT_UNDERPASS_JAW_FOSSIL    = ITEM_JAW_FOSSIL,
    DESERT_UNDERPASS_SAIL_FOSSIL   = ITEM_SAIL_FOSSIL,
};


extern bool8 gBikeCyclingChallenge;
extern u8 gBikeCollisions;
extern u16 gScrollableMultichoice_ScrollOffset;

u8 GetLeadMonIndex(void);
bool8 IsDestinationBoxFull(void);
u16 GetPCBoxToSendMon(void);
bool8 InMultiPartnerRoom(void);
void UpdateTrainerFansAfterLinkBattle(void);
void IncrementBirthIslandRockStepCount(void);
bool8 AbnormalWeatherHasExpired(void);
bool8 ShouldDoBrailleRegicePuzzle(void);
bool32 ShouldDoWallyCall(void);
bool32 ShouldDoScottFortreeCall(void);
bool32 ShouldDoScottBattleFrontierCall(void);
bool32 ShouldDoRoxanneCall(void);
bool32 ShouldDoRivalRayquazaCall(void);
bool32 CountSSTidalStep(u16 delta);
u8 GetSSTidalLocation(s8 *mapGroup, s8 *mapNum, s16 *x, s16 *y);
void ShowScrollableMultichoice(void);
void FrontierGamblerSetWonOrLost(bool8 won);
u8 TryGainNewFanFromCounter(u8 incrementId);
bool8 InPokemonCenter(void);
void SetShoalItemFlag(u16 unused);
void UpdateFrontierManiac(u16 daysSince);
void UpdateFrontierGambler(u16 daysSince);
void ResetCyclingRoadChallengeData(void);
bool8 UsedPokemonCenterWarp(void);
void ResetFanClub(void);
bool8 ShouldShowBoxWasFullMessage(void);
void SetPCBoxToSendMon(u8 boxId);
void PreparePartyForSkyBattle(void);
void GetObjectPosition(u16*, u16*, u32, u32);
bool32 CheckObjectAtXY(u32, u32);
bool32 CheckPartyHasSpecies(u32);

//Custom
void Handle_Wingull_Flag (void);
bool32 SetNewIVStatAll(void);
bool32 SetNewIVStat(void);
bool32 SwapPokemonGender(void);
void ChangeMonNature (void);
void DamageMon (void);
void Script_GiveMonSpecial (void);
void RegisterTalkedFossil (void);
void ReturnPokemonSpeciesFromOW (void);
#endif // GUARD_FIELD_SPECIALS_H
