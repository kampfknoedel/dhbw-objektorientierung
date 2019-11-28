#include "stdafx.h"
#include "player.h"
#include <iostream>


using namespace std;

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
	this->in_grid = false;
	this->alive = true;
}

bool player::fahren() {
	if (this->richtung_alt == 1) {
		return fahren_rechts();
	}
	if (this->richtung_alt == 2) {
		return fahren_links();
	}
	if (this->richtung_alt == 3) {
		return fahren_oben();
	}
	if (this->richtung_alt == 4) {
		return fahren_unten();
	}
}


bool player::fahren_links()
{
	this->pos_x = this->pos_x -3;
	this->in_grid = ((pos_x - 16) % 30);
	if (this->pos_x < 45) {
		return false;
	}
	return true;
	
}
bool player::fahren_rechts()
{
	this->pos_x = this->pos_x + 3;
	this->in_grid = ((pos_x - 16) % 30);
	if (this->pos_x >= 1876) {
		return false;
	}
	return true;
}
bool player::fahren_oben()
{
	this->pos_y = this->pos_y - 3;
	this->in_grid = ((pos_y - 16) % 30);
	if (this->pos_y < 45) {
		return false;
	}
	return true;
}
bool player::fahren_unten()
{
	this->pos_y = this->pos_y + 3;
	this->in_grid = ((pos_y - 16) % 30);
	if (this->pos_y > 1035) {
		return false;
	}
	return true;
}
