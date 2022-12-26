#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<windows.h>
#include<string.h>
int map[40][40]={0},n,m,lvl=0,step=0;
int dx[]={-1,0,1,0},dy[]={0,-1,0,1};
long long score=0;
bool box[40][40]={0};int px,py;
int trans(char c){
	switch(c){
		case 'w':case 'W':return 0;
		case 'a':case 'A':return 1;
		case 's':case 'S':return 2;
		case 'd':case 'D':return 3;
		case 'g':case 'G':return 10;
		case 'c':case 'C':return 11;
	}
	return -1;
}
bool read_map(){
	memset(box,0,sizeof(box));
	char *c=new char[128];
	sprintf(c,"library/levels/%d.txt",lvl);
	FILE* data=fopen(c,"r");
	if(!data)return 0;
	n=-1,m=-1;
	fscanf(data,"%d%d",&n,&m);
	if(n==-1&&m==-1)return 0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			fscanf(data,"%d",&map[i][j]);
			if(map[i][j]==3)px=i,py=j,map[i][j]=0;
			if(map[i][j]==2)box[i][j]=1,map[i][j]=0;
			if(map[i][j]==5)box[i][j]=1,map[i][j]=4;
		}
	fclose(data);
	return 1;
}
bool check(){
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)
			if(map[i][j]==4&&!box[i][j])return 0;
	return 1;
}
void print_map(){
	system("cls");
	printf("level: %d step: %d\ntotal score: %d\n\n",lvl,step,score);
	for(int i=0;i<m+2;i++)printf("##");
	puts("");
	for(int i=0;i<n;i++){
		char *str=new char[128],*iter=str+0;
		sprintf(iter,"##"),iter+=2;
		for(int j=0;j<m;j++){
			if(map[i][j]==1)sprintf(iter,"##"),iter+=2;
			else if(i==px&&j==py)sprintf(iter,"$$"),iter+=2;
			else if(box[i][j])
				if(map[i][j]==4)sprintf(iter,"{}"),iter+=2;
				else sprintf(iter,"[]"),iter+=2;
			else if(!map[i][j])sprintf(iter,"  "),iter+=2;
			else sprintf(iter,"()"),iter+=2;
		}
		sprintf(iter,"##");
		puts(str);
	}
	for(int i=0;i<m+2;i++)printf("##");
	puts("");
}
inline bool check(int x,int y){
	return x<0||x>=n||y<0||y>=m;
}
void write(int lvl,long long score){
	FILE* fp=fopen("library/state.txt","w");
	fprintf(fp,"%d %lld",lvl,score);fclose(fp);
}
void move(int fac,bool change=1){
	fac=trans(fac);
	if(fac==-1)return;
	if(fac==10){
		printf("Are you sure to clear the data?(Y/any keys): ");
		char c=getchar();
		if(c=='Y'||c=='y'){
			write(1,0);
			return exit(0);
		}else return;
	}
	if(fac==11){
		long long __level,__score;
		printf("Edit level: ");scanf("%d",&__level);
		printf("Edit score: ");scanf("%lld",&__score);
		FILE* fp=fopen("library/state.txt","w");
		fprintf(fp,"%d %lld",__level,__score);
		fclose(fp);
		return exit(0);
	}
	int pushx=px+dx[fac],pushy=py+dy[fac];
	if(check(pushx,pushy))return;
	if(!box[pushx][pushy]&&(!map[pushx][pushy]||map[pushx][pushy]==4)){
		px=pushx,py=pushy;
		step+=change;
		return;
	}else if(map[pushx][pushy]==1)return;
	else{
		int nx=pushx+dx[fac],ny=pushy+dy[fac];
		if(check(nx,ny))return;
		if(map[nx][ny]==1||box[nx][ny])return;
		else if(map[nx][ny]==4||!map[nx][ny]){
			box[nx][ny]=1;
			box[pushx][pushy]=0;
			px=pushx,py=pushy;
			step+=change;
		}
	}
}
void read_last(){
	FILE* fp=fopen("library/state.txt","r");
	fscanf(fp,"%d%d",&lvl,&score);lvl--;fclose(fp);
}
int main(){
	read_last();
	while(step=0,++lvl){
		if(!read_map()){
			printf("Congratulations!\nReplay?(Y/any keys): ");
			char c=getchar();
			if(c=='Y'||c=='y'){
				write(1,0);return 0;
			}
			while(getch()!=13)Sleep(50);return 0;
		}
		while(!check()){
			print_map();Sleep(50);
			move(getch());
		}
		print_map();printf("You win! Press Enter to continue...\n");
		score+=1000-step*3;write(lvl+1,score);
		while(getch()!=13)Sleep(50);
	}
}
