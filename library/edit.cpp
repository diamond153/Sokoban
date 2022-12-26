#include<stdlib.h>
#include<stdio.h>
char *c=new char[128];
int main(){
	while(printf("open file: "),scanf("%s",c)){
		char *str=new char[128];
		sprintf(str,"start levels/%s.txt",c);
		system(str);
	}
}
