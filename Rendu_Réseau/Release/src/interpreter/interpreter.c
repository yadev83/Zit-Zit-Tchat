#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "interpreter.h"

/*int main(void){
	char* string;
	defineStr(&string, 25);
	sprintf(string,"!login Martin Corto");
	char **data = interpreter(string);
	printf("%s\n", data[0]);
	return 0;
}*/

char *cmd;
char *element;

char *getCmd(){
	return cmd;
}

char *getElement(){
	return element;
}

void interpreter(char* msg){
	defineStr(&cmd, LENCMD);
	int iDetect;
	if(msg[0]!='!'){
		error();
	}
	else{
		iDetect=IDetect(msg);
		if(iDetect==1){
			error();
		}
		else{
			printf("%d\n", iDetect);
			defineStr(&element, strlen(msg)-iDetect);
			cutString(cmd, element, msg, iDetect);
		}
	}
}

void defineStr(char** str,int len){
	*str=malloc(len*sizeof(char));
	strcpy(*str, "");
}

void cutString(char* str1, char* str2, char* msg, int k){
	strcat(str2, &msg[k+1]);
	for (int i = 1; i < k; ++i)
		{
			str1[i-1]=msg[i];
		}
}

int IDetect(char* msg){
	int i=1;
	while(msg[i] != ' '){
		i++;
		if(i == strlen(msg))
			break;
	}
	return i;
}

void error(){
	printf("Erreur\n");
}