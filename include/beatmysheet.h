#ifndef BEATMYSHEET_H
#define BEATMYSHEET_H

#include <ncurses.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
  char stat_name[64];
  char stat_abrv[8];
  int stat_val;
  int stat_mod;
} CharStat;

typedef struct
{
  char *skill_name;
  CharStat skill_stat;
  bool skill_trained;
  bool skill_expertise;
} CharSkill;

typedef struct
{
  char pc_name[128];
  char pc_gender[64];
  float pc_height;
  float pc_weight;
  int pc_level;
  int pc_prof_bonus;
  CharStat pc_stats[6];
  CharSkill pc_skills[];
} PlayerCharacter;

PlayerCharacter* createCharacter();
CharStat generateStat(char *stat_n, char *stat_abv, int stat_v);

#endif
