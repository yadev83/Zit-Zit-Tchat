#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "interpreter.h"
int main(void){
	char* string;
	defineStr(&string, 25);
	sprintf(string,"!login Martin Corto");
	printf("%s\n", string);
	interpreter(string);

	return 0;
}
void interpreter(char* msg){
	char *cmd;
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
		char* element;
		defineStr(&element, strlen(msg)-iDetect);
		cutString(cmd, element, msg, iDetect);
		
		printf("%s\n", cmd);
		printf("%s\n", element);
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
	free(msg);
}

int IDetect(char* msg){
	int i=1;
	while(msg[i] != ' '){
		i++;
	}
	return i;
}

void error(){
	printf("Erreur\n");
}