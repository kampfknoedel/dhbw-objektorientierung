#pragma once
class player
{
public:
	int pos_x;
	int pos_y;

	int richtung;		// 1 = rechts; 2 = links; 3 = oben, 4 = unten

	void field_to_pixel(int field_x, int field_y);

	void fahren_rechts();
	void fahren_links();
	void fahren_oben();
	void fahren_unten();

	player();
	~player();
	
};

