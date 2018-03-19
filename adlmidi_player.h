#ifndef ADLMIDI_PLAYER_H_
#define ADLMIDI_PLAYER_H_

/*
 * Bank 0, AIL (Star Control 3, Albion, Empire 2, Sensible Soccer, Settlers 2, many others)
 * Bank 1, Bisqwit (selection of 4op and 2op)
 * Bank 2, HMI (Descent, Asterix)
 * Bank 3, HMI (Descent:: Int)
 * Bank 4, HMI (Descent:: Ham)
 * Bank 5, HMI (Descent:: Rick)
 * Bank 6, HMI (Descent 2)
 * Bank 7, HMI (Normality)
 * Bank 8, HMI (Shattered Steel)
 * Bank 9, HMI (Theme Park)
 * Bank 10, HMI (3d Table Sports, Battle Arena Toshinden)
 * Bank 11, HMI (Aces of the Deep)
 * Bank 12, HMI (Earthsiege)
 * Bank 13, HMI (Anvil of Dawn)
 * Bank 14, DMX (Doom           :: partially pseudo 4op)
 * Bank 15, DMX (Hexen, Heretic :: partially pseudo 4op)
 * Bank 16, DMX (MUS Play       :: partially pseudo 4op)
 * Bank 17, AIL (Discworld, Grandest Fleet, Pocahontas, Slob Zone 3d, Ultima 4, Zorro)
 * Bank 18, AIL (Warcraft 2)
 * Bank 19, AIL (Syndicate)
 * Bank 20, AIL (Guilty, Orion Conspiracy, Terra Nova Strike Force Centauri :: 4op)
 * Bank 21, AIL (Magic Carpet 2)
 * Bank 22, AIL (Nemesis)
 * Bank 23, AIL (Jagged Alliance)
 * Bank 24, AIL (When Two Worlds War :: 4op, MISSING INSTRUMENTS)
 * Bank 25, AIL (Bards Tale Construction :: MISSING INSTRUMENTS)
 * Bank 26, AIL (Return to Zork)
 * Bank 27, AIL (Theme Hospital)
 * Bank 28, AIL (National Hockey League PA)
 * Bank 29, AIL (Inherit The Earth)
 * Bank 30, AIL (Inherit The Earth, file two)
 * Bank 31, AIL (Little Big Adventure :: 4op)
 * Bank 32, AIL (Wreckin Crew)
 * Bank 33, AIL (Death Gate)
 * Bank 34, AIL (FIFA International Soccer)
 * Bank 35, AIL (Starship Invasion)
 * Bank 36, AIL (Super Street Fighter 2 :: 4op)
 * Bank 37, AIL (Lords of the Realm :: MISSING INSTRUMENTS)
 * Bank 38, AIL (SimFarm, SimHealth :: 4op)
 * Bank 39, AIL (SimFarm, Settlers, Serf City)
 * Bank 40, AIL (Caesar 2 :: partially 4op, MISSING INSTRUMENTS)
 * Bank 41, AIL (Syndicate Wars)
 * Bank 42, AIL (Bubble Bobble Feat. Rainbow Islands, Z)
 * Bank 43, AIL (Warcraft)
 * Bank 44, AIL (Terra Nova Strike Force Centuri :: partially 4op)
 * Bank 45, AIL (System Shock :: partially 4op)
 * Bank 46, AIL (Advanced Civilization)
 * Bank 47, AIL (Battle Chess 4000 :: partially 4op, melodic only)
 * Bank 48, AIL (Ultimate Soccer Manager :: partially 4op)
 * Bank 49, AIL (Air Bucks, Blue And The Gray, America Invades, Terminator 2029)
 * Bank 50, AIL (Ultima Underworld 2)
 * Bank 51, AIL (Kasparov's Gambit)
 * Bank 52, AIL (High Seas Trader :: MISSING INSTRUMENTS)
 * Bank 53, AIL (Master of Magic, Master of Orion 2 :: 4op, std percussion)
 * Bank 54, AIL (Master of Magic, Master of Orion 2 :: 4op, orchestral percussion)
 * Bank 55, SB (Action Soccer)
 * Bank 56, SB (3d Cyberpuck :: melodic only)
 * Bank 57, SB (Simon the Sorcerer :: melodic only)
 * Bank 58, OP3 (The Fat Man 2op set)
 * Bank 59, OP3 (The Fat Man 4op set)
 * Bank 60, OP3 (JungleVision 2op set :: melodic only)
 * Bank 61, OP3 (Wallace 2op set, Nitemare 3D :: melodic only)
 * Bank 62, TMB (Duke Nukem 3D)
 * Bank 63, TMB (Shadow Warrior)
 * Bank 64, DMX (Raptor)
 * Bank 65, OP3 (Modded GMOPL by Wohlstand)
 * Bank 66, SB (Jammey O'Connel's bank)
 * Bank 67, TMB (Default bank of Build Engine)
 * Bank 68, WOPL (4op bank by James Alan Nguyen and Wohlstand)
 * Bank 69, TMB (Blood)
 * Bank 70, TMB (Lee)
 * Bank 71, TMB (Nam)
 * Bank 72, WOPL (DMXOPL3 bank by Sneakernets)
 * Bank 73, EA (Cartooners)
 */

extern "C"
{
    void adlPlay(const char *filename);
    void adlSetBank(int bankId);
    void adlSetVolume(int volume);
    void adlPause();
    void adlResume();
    void adlStop();
    int adlSeek();
}

#endif /* ADLMIDI_PLAYER_H_ */
