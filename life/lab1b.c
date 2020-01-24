#include "lifegame.c"
#define NUM_GENERATIONS 100

void next_generation(void);
int get_next_state(int x, int y);
int num_neighbors(int x, int y);

int main(int argc, char ** argv)
{
	int n;
	image My_image;
	My_image.mx=get_world_width();
	My_image.my=get_world_height();
	init_image(&My_image);
    initialize_world_from_file("glider.txt");
	for (n = 0; n < NUM_GENERATIONS; n++){
		next_generation();
		move(&My_image);
		save_world_to_file(&My_image,n);
	}
	free_image(&My_image);
	return 0;
}

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
