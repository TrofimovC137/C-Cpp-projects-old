#include "lifegame.c"
#define NUM_GENERATIONS 100

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


