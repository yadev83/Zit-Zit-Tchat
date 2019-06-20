#include <ncurses.h> 
#include <unistd.h> 

#include "gfx.h"

WINDOW *display;
WINDOW *input;

int parent_x;
int parent_y;
static int msg_size = 3; 

void createDisplay(void){ 
    initscr(); 
    
    noecho(); 
    curs_set(FALSE); 
    
    // get our maximum window dimensions 
    getmaxyx(stdscr, parent_y, parent_x); 
    
    // set up initial windows 
    display = newwin(parent_y - msg_size, parent_x, 0, 0); 
    input = newwin(msg_size, parent_x, parent_y - msg_size, 0); 
    
    // draw to our windows 
    drawBorders(display);
    drawBorders(input);
    
    displayContent("Server : ", "Input : ");

}

void refreshDisplay(void){
    int new_y, new_x;
    getmaxyx(stdscr, new_y, new_x); 
    if (new_y != parent_y || new_x != parent_x) { 
        parent_x = new_x; 
        parent_y = new_y; 
        wresize(display, new_y - msg_size, new_x); 
        wresize(input, msg_size, new_x); 
    }
    drawBorders(display); 
    drawBorders(input); 
    wrefresh(display); 
    wrefresh(input);  
}

void closeDisplay(void){
    delwin(display); 
    delwin(input); 
    endwin(); 
}

void drawBorders(WINDOW *screen){ 
    int x, y, i; 
    getmaxyx(screen, y, x); 
    
    // 4 corners 
    mvwprintw(screen, 0, 0, "+"); 
    mvwprintw(screen, y - 1, 0, "+"); 
    mvwprintw(screen, 0, x - 1, "+"); 
    mvwprintw(screen, y - 1, x - 1, "+"); 
    
    // sides 
    for(i = 1; i < (y - 1); i++){ 
        mvwprintw(screen, i, 0, "|"); 
        mvwprintw(screen, i, x - 1, "|"); 
    } 
    // top and bottom 
    for(i = 1; i < (x - 1); i++){ 
        mvwprintw(screen, 0, i, "-"); 
        mvwprintw(screen, y - 1, i, "-");
    } 
}

void displayContent(char *server, char *client){
    if(server != NULL)
        mvwprintw(display, 1, 1, server); 
    
    if(client != NULL)
        mvwprintw(input, 1, 1, client); 
}