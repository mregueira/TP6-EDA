#include "stdafx.h"
#include "graphic_movement.h"

#include <iostream>



graphic_movement::graphic_movement()
{
	init();
	for (unsigned int i = 0; i < 6; i++)
	{
		for (unsigned int j = 0; j < cant_imgs[i]; j++)
		{
			imgs[i][j] = nullptr;
		}
	}
	background = nullptr;

}

void graphic_movement::init() {

	prefixs[1] = "Images/Explosion 1/Explosion 1-F";
	prefixs[2] = "Images/Explosion 2/Explosion 2-F";
	prefixs[0] = "Images/Cat Running/Cat Running-F";
	prefixs[3] = "Images/Homer Dance/homerdance-F";
	prefixs[4] = "Images/Super Mario/Super Mario Running-F";
	prefixs[5] = "Images/Sonic/Sonic Running-F";

	prefix_background = "Images/windows";
	prefix_backgroundwoalpha = "Images/windows";

	extension = ".png";

	cant_imgs[0] = 12;
	cant_imgs[1] = 8;
	cant_imgs[2] = 48;
	cant_imgs[3] = 10;
	cant_imgs[4] = 12;
	cant_imgs[5] = 10;


}

graphic_movement::~graphic_movement()
{
	for (unsigned int i = 0; i < 6; i++)
	{
		for (unsigned int j = 0; j < cant_imgs[i]; j++)
		{
			al_destroy_bitmap(imgs[i][j]);
		}
	}
}




void graphic_movement::load_imgs() {
	for (unsigned int i = 0; i < 6; i++)
	{
		for (unsigned int j = 0; j < cant_imgs[i]; j++)
		{
			string aux = prefixs[i] + to_string(j + 1) + extension;
			if ((imgs[i][j] = al_load_bitmap(&aux[0])) == NULL)
				int h = 1;
		}
	}
}



void graphic_movement::load_background()
{
	string aux = prefix_background + extension;
	background = al_load_bitmap(&aux[0]);
}

void graphic_movement::load_backgroundwoalpha()
{
	string aux2 = prefix_backgroundwoalpha + extension;
	backgroundwoalpha = al_load_bitmap(&aux2[0]);
}

void graphic_movement::start_gif(char gif_id)
{
	switch (gif_id)		//obs: j: pixeles por unidad de tiempo (o pixel_rate).
	{
	case 0: //GATO ('A')
		for (unsigned int pixelRate = 0; pixelRate < 800;) 
		{
			for (unsigned int i = 0; i < cant_imgs[gif_id]; i++)
			{
				al_draw_scaled_bitmap(imgs[0][i], 0, 0, 688, 387, pixelRate, 300, 100, 177, 0);
				al_flip_display();
				al_rest(0.1);
				pixelRate = pixelRate + 20;
				load_background();
				flip_background();
			}
		}
		break;


	case 1: //'B'
		for (unsigned int i = 0; i < cant_imgs[1]; i++)
		{
			al_draw_scaled_bitmap(imgs[1][i], 0, 0, 450, 274, 0, 0, 800, 600, 0);
			al_flip_display();
			al_rest(0.120);
		}
		break;

	case 2: //'C'
		for (unsigned int i = 0; i < cant_imgs[2]; i++)
		{
			al_draw_scaled_bitmap(imgs[2][i], 0, 0, 256, 256, 0, 0, 800, 600, 0);
			al_flip_display();
			al_rest(0.100);
		}
		break;

	case 3:  //'D'
		for (unsigned int pixelRate = 0; pixelRate < 800;)
		{
			for (unsigned int i = 0; i < cant_imgs[3]; i++)
			{
				al_draw_bitmap(imgs[3][i], pixelRate, 200, 0);
				al_flip_display();
				al_rest(0.1);
				pixelRate = pixelRate + 100;
				load_background();
				flip_background();
			}
		}
		break;

	case 4: //'E'
		for (unsigned int pixelRate = 0; pixelRate < 800;)
		{
			for (unsigned int i = 0; i < cant_imgs[4]; i++)
			{
				al_draw_scaled_bitmap(imgs[4][i], 0, 0, 650, 660, pixelRate, 300, 200, 200, 0);
				al_flip_display();
				al_rest(0.04);
				pixelRate = pixelRate + 2;
				load_background();
				flip_background();
			}
		}
		break;

	case 5: //'F'
		unsigned int k = 1;
		for (unsigned int pixelRate = 0; pixelRate < 800;)
		{
			for (unsigned int i = 0; i < cant_imgs[5]; i++)
			{
				al_draw_scaled_bitmap(imgs[5][i], 0, 0, 700, 600, pixelRate, 300, 200, 180, 1);
				al_flip_display();
				al_rest(0.06);
				if (k++ > 3)
				{
					pixelRate = pixelRate + 70;
					k = 1;
				}
				load_background();
				flip_background();
			}
		}
		break;


	}
}
void graphic_movement::flip_background()
{
	al_draw_scaled_bitmap(background, 0, 0, 1920, 696, 0, 0, 1920, 696, 0);
}


void graphic_movement::flip_backgroundwoalpha() {
	al_draw_scaled_bitmap(backgroundwoalpha, 0, 0, 1200, 800, 0, 0, 1920, 696, 0);
}
