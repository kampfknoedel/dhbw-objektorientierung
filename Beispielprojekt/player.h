#pragma once
class player
{
public:
	int pos_x;
	int pos_y;
	bool in_grid = false;
	bool alive = true;
	int richtung;		// 1 = rechts; 2 = links; 3 = oben, 4 = unten
	int richtung_alt;
	bool last_field_feld = 0;

	void field_to_pixel(int field_x, int field_y);

	bool fahren_rechts();
	bool fahren_links();
	bool fahren_oben();
	bool fahren_unten();
	bool fahren();

	player();
	~player();
	
};

