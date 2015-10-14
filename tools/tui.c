#include <curses.h>
#include <menu.h>
#include <stdio.h>
#include <string.h>
#include <locale.h>

int main()
{
	initscr();
	setlocale(LC_ALL,"zh_CN.utf-8");

	WINDOW *pwin;
	long row,col;

	getmaxyx(stdscr, row,col);

	pwin = newwin(row/2, col, 0, 0);
	// box(pwin,0,0);
	scrollok(pwin, true);
	wprintw(pwin, "---------什么 32121 -------\n");
	wrefresh(pwin);

	ITEM *pit_menu;
	char name[] = "name";
	char description[] = "description";

	pit_menu = new_item(name, description);
	if (NULL == pit_menu) {
		wprintw(pwin,"new_item error\n");
		return 0;
	}
	else {
		wprintw(pwin,"new_item success\n");
	}
	wrefresh(pwin);

	// char ch;
	// while( ch = getch()) {
	// 	// if (ch == '\n') {
	// 	// 	break;
	// 	// }
	// 	// else 
	// 	{
	// 		wprintw(pwin,"%c",ch);
	// 		wrefresh(pwin);
	// 	}
	// }
	printf("1\r\n");
	printf("1\r\n");
	printf("1\r\n");
	printf("1\r\n");

	return 0;
}


#include <curses.h>
#include <locale.h>
#include <string.h>

int ma3in(void)
{
    char *msg="你好 世界!";

    setlocale(LC_ALL,"");
    initscr();
    noecho();
    curs_set(FALSE);
    cbreak();

    mvprintw(LINES/2,COLS/2-strlen(msg)/2,msg);
    refresh();

    getch();
    endwin();
    return 0;
}
