#include <beatmysheet.h>

PlayerCharacter* createCharacter()
{
  PlayerCharacter* newPC = calloc(1, sizeof(PlayerCharacter));

  strcpy(newPC->pc_name, "Test Name");
  strcpy(newPC->pc_gender, "Male");
  newPC->pc_height = 180;
  newPC->pc_weight = 69;
  
  clear();
  printw("Generating stats");
  getch();
  /* Generate stats */
  newPC->pc_stats[0] = generateStat("Strength", "STR", 10);
  newPC->pc_stats[1] = generateStat("Dexterity", "DEX", 10);
  newPC->pc_stats[2] = generateStat("Constitution", "CON", 10);
  newPC->pc_stats[3] = generateStat("Intelligence", "INT", 10);
  newPC->pc_stats[4] = generateStat("Wisdom", "WIS", 10);
  newPC->pc_stats[5] = generateStat("Charisma", "CHA", 10);

  return newPC;
}

CharStat generateStat(char *stat_n, char *stat_abv, int stat_v)
{
  CharStat output_stat;
  strcpy(output_stat.stat_name, stat_n);
  strcpy(output_stat.stat_abrv, stat_abv);
  output_stat.stat_val = stat_v;
  output_stat.stat_mod = (int)((stat_v - 10)/2);
  return output_stat;
}
