#include<stdio.h>
#include<stdlib.h>
int main(){
	int *level=new int,*score=new int;
	printf("Edit level: ");
	scanf("%d",level);
	printf("Edit score: ");
	scanf("%d",score);
	FILE* fp=fopen("state.txt","w");
	fprintf(fp,"%d %d",*level,*score);
	fclose(fp);
	return 0;
}
