#include <stdio.h>
#include <ncurses.h>

int main(int argc, char ** argv) {
    initscr();
    printw("hello, world\n");
    refresh();
    getch();
    endwin();
    return 0;
}
