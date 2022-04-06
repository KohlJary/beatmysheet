#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <panel.h>
#include <pwd.h>
#include <beatmysheet.h>

#define NLINES 20
#define NCOLS 40

int startx = 0;
int starty = 0;

char *main_menu_choices[] = {
  "Create Character",
  "Load Character",
  "Import Character",
  "Delete Character",
  "Exit Program"
};
int n_main_choices = sizeof(main_menu_choices) / sizeof(char *);

struct stat st = {0};

const char *homedir;
const char* programdir = "/.beatmysheet";
const char *filedir;

PlayerCharacter* active_pc;

void initialize_dir();
void print_welcome_scrn(WINDOW *menu_win, int highlight);

int main(int argc, char *argv[])
{
  /* Initialize directory */
  initialize_dir();

  /* Initialize ncurses */
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(0);

  /* Initialize colors */
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_GREEN, COLOR_BLACK);
  init_pair(3, COLOR_BLUE, COLOR_BLACK);
  init_pair(4, COLOR_CYAN, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);
  init_pair(6, COLOR_MAGENTA, COLOR_BLACK);

  /* Initialize window */
  WINDOW *menu_win;
  int highlight = 1;
  int choice = 0;
  int ch;

  startx = (80 - NCOLS)/ 2;
  starty = (24 - NLINES)/ 2;

  menu_win = newwin(NLINES, NCOLS, starty, startx);
  keypad(menu_win, TRUE);

  print_welcome_scrn(menu_win, highlight);

  while(1)
  {
    ch = wgetch(menu_win);
    switch(ch)
    {
      case KEY_UP:
      case 'k':
        if(highlight == 1)
          highlight = n_main_choices;
        else
          --highlight;
        break;
      case KEY_DOWN:
      case 'j':
        if(highlight == n_main_choices)
          highlight == 1;
        else
          ++highlight;
        break;
      case 10:
        choice = highlight;
        break;
      default:
        refresh();
        break;
    }
    print_welcome_scrn(menu_win, highlight);
    if(choice != 0)
    {
      switch(choice)
      {
        case 1:
          active_pc = createCharacter();
          clear();
          printw("Created character: %s", active_pc->pc_name);
          refresh();
          print_welcome_scrn(menu_win, highlight);
          choice=0;
          break;
        default:
          break;
      }
    }
    if(choice != 0)
      break;
  }
  mvprintw(23, 0,"You chose choice %d with choice string %s\n", choice, main_menu_choices[choice-1]);
  clrtoeol();
  refresh();
  getch();
  endwin();
  return 0;
}

void print_welcome_scrn(WINDOW *menu_win, int highlight)
{
  int x, y, i;

  x=2;
  y=8;
  box(menu_win, 0, 0);
  if(active_pc != NULL)
  {
    mvwprintw(menu_win, 1, x, "Active Character: %s", active_pc->pc_name);
    mvwprintw(menu_win, 2, x, "Welcome to BeatMySheet!");
    mvwprintw(menu_win, 3, x, "Please select a mode:");
  }
  else
  {
    mvwprintw(menu_win, 1, x, "Welcome to BeatMySheet!");
    mvwprintw(menu_win, 2, x, "Please select a mode:");
  }
  for(i = 0; i < n_main_choices; ++i)
  {
    if(highlight == i+1)
    {
      wattron(menu_win, A_REVERSE);
      mvwprintw(menu_win, y, x, "%d: %s", i+1, main_menu_choices[i]);
      wattroff(menu_win, A_REVERSE);
    }
    else
      mvwprintw(menu_win, y, x, "%d: %s", i+1, main_menu_choices[i]);
    ++y;
  }
  wrefresh(menu_win);
}

void initialize_dir()
{
  char *workingdir;
  /* Get the user's home directory. */
  if((homedir = getenv("HOME")) == NULL)
  {
    homedir = getpwuid(getuid())->pw_dir;
  }
  /* Get the working path for files */
  workingdir = malloc(strlen(homedir)+1+13);
  strcpy(workingdir, homedir);
  strcat(workingdir, programdir);
  filedir = workingdir;
  if(stat(filedir, &st) == -1)
  {
    printf("Directory $HOME/.beatmysheet does not exist, creating...\n");
    mkdir(filedir, 0700);
  }
  else
  {
    printf("Directory $HOME/.beatmysheet does exist.\n");
  }
}
