#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{
}

void player::field_to_pixel(int field_x, int field_y)
{
	this->pos_x = 45 + (field_x * 30) - 29;
	this->pos_y = 45 + (field_y * 30) - 29;
}

void player::fahren_rechts()
{
	this->pos_x = this->pos_x +3;
	this->in_grid = ((pos_x - 16) % 30);
}
void player::fahren_links()
{
	this->pos_x = this->pos_x - 3;
	this->in_grid = ((pos_x - 16) % 30);
}
void player::fahren_oben()
{
	this->pos_y = this->pos_y - 3;
	this->in_grid = ((pos_y - 16) % 30);
}
void player::fahren_unten()
{
	this->pos_y = this->pos_y + 3;
	this->in_grid = ((pos_y - 16) % 30);
}
