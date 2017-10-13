#pragma once
#include <allegro5\allegro5.h>
#include <string>

using namespace std;

class graphic_movement
{

public:
	graphic_movement();
	void init();

	void load_imgs();

	void load_background();


	void flip_background();

	void start_gif(char GIF_ID);



	void load_backgroundwoalpha();

	void flip_backgroundwoalpha();

	~graphic_movement();

private:
	unsigned int cant_imgs[6];
	/*unsigned int cant_cat;    0
	unsigned int cant_exp1;		1
	unsigned int cant_exp2;		2
	unsigned int cant_homer;	3
	unsigned int cant_sonic;	4
	unsigned int cant_mario;	5
	*/
	string prefixs[6];
	/*string prefix_cat;
	string prefix_exp1;
	string prefix_exp2;
	string prefix_homer;
	string prefix_sonic;
	string prefix_mario;*/

	string prefix_background;
	string prefix_backgroundwoalpha;
	string extension;

	ALLEGRO_BITMAP * imgs_cat[12];
	ALLEGRO_BITMAP * imgs_exp1[8];
	ALLEGRO_BITMAP * imgs_exp2[48];
	ALLEGRO_BITMAP * imgs_homer[10];
	ALLEGRO_BITMAP * imgs_mario[12];
	ALLEGRO_BITMAP * imgs_sonic[10];

	ALLEGRO_BITMAP * * imgs[6] = { imgs_cat,imgs_exp1,imgs_exp2,imgs_homer,imgs_mario,imgs_sonic };

	ALLEGRO_BITMAP * background;
	ALLEGRO_BITMAP * backgroundwoalpha;

};


