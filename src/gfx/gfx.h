#ifndef __GFX_H
#define __GFX_H

void createDisplay(void);
void refreshDisplay(void);
void closeDisplay(void);
void drawBorders(WINDOW *screen);
void displayContent(char *server, char *client);

#endif //__GFX_H