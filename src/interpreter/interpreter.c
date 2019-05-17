#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "interpreter.h"
int main(void){
	char string[20];
	sprintf(string,"!login Martin Corto");
	printf("%s\n", string);
	interpreter(string);

	return 0;
}
void interpreter(char* msg){
	char cmd[LENCMD]="";
	int iDetect;
	//printf("%d\n", strcmp(&msg[0], "!"));
	if(msg[0]!='!'){
		error();
	}
	else{
		iDetect=commandDetect(msg);
		char* element;
		element=malloc((strlen(msg)-iDetect)*sizeof(char));
		strcpy(element, "");
		strcat(element, &msg[iDetect+1]);
		for (int i = 1; i < iDetect; ++i)
		{
			cmd[i-1]=msg[i];
		}
		printf("%s\n", cmd);
		printf("%s\n", element);
	}
}

int commandDetect(char* msg){
	int i=1;
	while(msg[i] != ' '){
		i++;
	}
	return i;
}

void error(){
	printf("Erreur\n");
}