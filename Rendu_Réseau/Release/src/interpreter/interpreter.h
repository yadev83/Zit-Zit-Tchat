#define LENCMD 10

char *getCmd();
char *getElement();

void interpreter(char* msg);
void cutString(char* str1, char* str2, char* msg, int k);
int IDetect(char* msg);
void defineStr(char** str,int len);
void error();