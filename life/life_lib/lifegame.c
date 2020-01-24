#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "lifegame.h"
#define WORLDWIDTH 50
#define WORLDHEIGHT 50

static int world[WORLDWIDTH][WORLDHEIGHT];
static int nextstates[WORLDWIDTH][WORLDHEIGHT];
typedef struct image{
    int** points;
    int mx,my;
}image;
void init_image(image* My_image){
    int i,j;
    My_image->points=malloc(sizeof(int*)*My_image->mx);
    for (i=0;i<My_image->mx;i++){
        My_image->points[i]=malloc(sizeof(int)*My_image->my);
    }
    for (i=0;i<My_image->mx;i++){
        for(j=0;j<My_image->mx;j++){
            My_image->points[i][j]==1;
        }
    }
}
void free_image(image* My_image){
    int i,j;
    for (i=0;i<My_image->mx;i++){
            free(My_image->points[i]);
    }
    free(My_image->points);
    My_image->points=0;
    My_image->mx=0;
    My_image->my=0;
}
void move(image* My_image){
    int i,j;
    for (i=0;i<WORLDWIDTH;i++){
        for (j=0;j<WORLDHEIGHT;j++){
            My_image->points[i][j]=world[i][j];
        }
    }
}
int len_int(int value){
    int i=0;
    while (value!=0){
        value/=10;
        i++;
    }
    return i;
}
void filename(char* fname,int value){
    int i,index;
    fname[0]='i';
    fname[1]='m';
    fname[2]='a';
    fname[3]='g';
    fname[4]='e';
    index=5+len_int(value);
    for(i=4+len_int(value);i>4;i--){
        fname[i]=(char)(value%10+48);
        value/=10;
    }
    fname[index]='.';
    fname[index+1]='P';
    fname[index+2]='P';
    fname[index+3]='M';
    fname[index+4]='\0';
}
void Print_int(char* str,int value){
    int i,index;
    index=len_int(value);
    for(i=len_int(value)-1;i>=0;i--){
        str[i]=(char)(value%10+48);
        value/=10;
    }
    str[index]='\n';
    str[index+1]='\0';
}
void save_world_to_file(image* My_image,int value){
    int i,j;
    char mx[10],my[10],fname[100];
    FILE* file;
    filename(fname,value);
    file=fopen(fname,"w");
    fprintf(file,"P1\n");
    Print_int(mx,My_image->mx);
    Print_int(my,My_image->my);
    fprintf(file,mx);
    fprintf(file,my);
    for (i=0;i<My_image->mx;i++){
        for (j=0;j<My_image->my;j++){
            fputc(My_image->points[i][j]+48,file);
        }
        fprintf(file,"\n");
    }
    fclose(file);
}
void initialize_world_from_file(const char * filename) {
    if (filename=='\0'){
        filename="grider.txt";
    }
    FILE *fp;
    int i,j;
    fp=fopen(filename,"r");
    for (i=0;i<WORLDWIDTH;i++){
        for (j=0;j<WORLDHEIGHT;j++){
            world[i][j]=(int)(fgetc(fp))-48;
            }
        fgetc(fp);
    }
    fclose(fp);
}

void initialize_world(void) {
	int i, j;

	for (i = 0; i < WORLDWIDTH; i++)
		for (j = 0; j < WORLDHEIGHT; j++)
			world[i][j] = nextstates[i][j] = DEAD;
	/* pattern "glider" */
	world[1][2] = ALIVE;
	world[3][1] = ALIVE;
	world[3][2] = ALIVE;
	world[3][3] = ALIVE;
	world[2][3] = ALIVE;
}

int get_world_width(void) {
	return WORLDWIDTH;
}

int get_world_height(void) {
	return WORLDHEIGHT;
}

int get_cell_state(int x, int y) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT)
		return DEAD;
	return world[x][y];
}

void set_cell_state(int x, int y, int state) {
	if (x < 0 || x >= WORLDWIDTH || y < 0 || y >= WORLDHEIGHT) {
		fprintf(stderr,"Error: coordinates (%d,%d) are invalid.\n", x, y);
		abort();
	}
	nextstates[x][y] = state;
}

void finalize_evolution(void) {
	int x, y;
	for (x = 0; x < WORLDWIDTH; x++) {
		for (y = 0; y < WORLDHEIGHT; y++) {
			world[x][y] = nextstates[x][y];
			nextstates[x][y] = DEAD;
		}
	}
}

/*void output_world(void) {
	char worldstr[2*WORLDWIDTH+2];
	int i, j;

	worldstr[2*WORLDWIDTH+1] = '\0';
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
	for (i = 0; i <= 2*WORLDWIDTH; i+=2)
		worldstr[i] = '|';
	for (i = 0; i < WORLDHEIGHT; i++) {
		for (j = 0; j < WORLDWIDTH; j++)
			worldstr[2*j+1] = world[j][i] == ALIVE ? CHAR_ALIVE : CHAR_DEAD;
		puts(worldstr);
	}
	worldstr[0] = '+';
	for (i = 1; i < 2*WORLDWIDTH; i++)
		worldstr[i] = '-';
	worldstr[2*WORLDWIDTH] = '+';
	puts(worldstr);
}*/
void next_generation(void) {
    int i,j;
    int mx=get_world_width(),my=get_world_height();
    for (i=0;i<mx;i++){
        for(j=0;j<my;j++){
            set_cell_state(i ,j ,get_next_state(i,j));
        }
    }
	finalize_evolution();
}

int get_next_state(int x, int y) {
    switch (num_neighbors(x,y)){
    case (3):
        return ALIVE;
    case (2):
        return get_cell_state(x,y);
    default:
        return DEAD;
    }
}
int num_neighbors(int x, int y) {
    int Mas_x[]={-1,0,1,-1,1,-1,0,1};
    int Mas_y[]={-1,-1,-1,0,0,1,1,1};
    int i,number=0;
    for(i=0;i<8;i++){
        if (get_cell_state(x+Mas_x[i], y+Mas_y[i]) == ALIVE){
            number++;
        }
    }
    return number;
}
