#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Vektor2d.h"
#include "player.h"
using namespace std;
// Simulationsgeschwindigkeit
const double DT = 100.0;




class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(1920, 1080, true)
		, font (50)
	{
		set_caption("Gosu Tutorial Game mit Git");
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt

	
	player p1, p2;
	int start = 0;
	int winner = 0;
	string score_txt;
	std::stringstream score_string;

	enum zustand {
		frei,
		p1_spur,
		p1_feld,
		p2_spur,
		p2_feld
	};

	zustand kaestle[61][33];
	
	enum zustand_chapter {
		startseite,
		spiel,
		ende,
	};
	zustand_chapter chapter;
	
	Gosu::Font font;

	void draw() override
	{
		// Notizen: Bildbereich: 1830x990 pixel 
		// Bei 30x30 Spielergröße 61x33 Spielfelder 
		// Rand: 45x45
		
		if (chapter == startseite) {
			Gosu::Graphics::draw_rect(
				0, 0, 1920, 1080, Gosu::Color::GRAY,
				0.0
			);
			font.draw_rel(
				"Press [RETURN] for Start.",
				960, 540, 0.0, 0.5, 0.5, 1, 1, Gosu::Color::WHITE);
		}

		if (chapter == spiel) {


			Gosu::Graphics::draw_rect(
				0, 0, 1920, 1080, Gosu::Color::GRAY,
				0.0
			);

			for (int i = 0; i < 61; ++i) {
				for (int j = 0; j < 33; ++j)
				{
					if (kaestle[i][j] == frei) {
						Gosu::Graphics::draw_rect(
							(45 + (i + 1) * 30 - 29), (45 + (j + 1) * 30 - 29), 30, 30, Gosu::Color::BLACK,
							0.0
						);
					}
					if (kaestle[i][j] == p1_spur) {
						Gosu::Graphics::draw_rect(
							(45 + (i + 1) * 30 - 29), (45 + (j + 1) * 30 - 29), 30, 30, Gosu::Color::Color(0xFA, 0x88, 0x88),
							0.0
						);
					}
					if (kaestle[i][j] == p1_feld) {
						Gosu::Graphics::draw_rect(
							(45 + (i + 1) * 30 - 29), (45 + (j + 1) * 30 - 29), 30, 30, Gosu::Color::Color(0xFF, 0x60, 0x60),
							0.0
						);
					}
					if (kaestle[i][j] == p2_spur) {
						Gosu::Graphics::draw_rect(
							(45 + (i + 1) * 30 - 29), (45 + (j + 1) * 30 - 29), 30, 30, Gosu::Color::Color(0x88, 0x88, 0xFA),
							0.0
						);
					}
					if (kaestle[i][j] == p2_feld) {
						Gosu::Graphics::draw_rect(
							(45 + (i + 1) * 30 - 29), (45 + (j + 1) * 30 - 29), 30, 30, Gosu::Color::Color(0x60, 0x60, 0xFF),
							0.0
						);
					}
 				}
			}

			Gosu::Graphics::draw_rect(
				p1.pos_x, p1.pos_y, 30, 30, Gosu::Color::RED,
				0.0
			);
			Gosu::Graphics::draw_rect(
				p2.pos_x, p2.pos_y, 30, 30, Gosu::Color::BLUE,
				0.0
			);
			font.draw_rel(
				score_txt,
				960, 20, 0.0, 0.5, 0.5, 1, 1, Gosu::Color::WHITE);

		}
		if (chapter == ende) {
			Gosu::Graphics::draw_rect(
				0, 0, 1920, 1080, Gosu::Color::WHITE,
				0.0
			);
			if (winner == 1) {
				font.draw_rel(
					"Rot hat gewonnen!",
					960, 540, 0.0, 0.5, 0.5, 3, 3, Gosu::Color::RED);
			}
			if (winner == 2) {
				font.draw_rel(
					"Blau hat gewonnen!",
					960, 540, 0.0, 0.5, 0.5, 3, 3, Gosu::Color::BLUE);
			}
			font.draw_rel(
				"Press [RETURN] for new game",
				960, 750, 0.0, 0.5, 0.5, 1, 1, Gosu::Color::BLACK);
			font.draw_rel(
				"Press [ESC] for exit.",
				960, 800, 0.0, 0.5, 0.5, 1, 1, Gosu::Color::BLACK);
			font.draw_rel(
				score_txt,
				960, 300, 0.0, 0.5, 0.5, 1, 1, Gosu::Color::BLACK);
		}
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
		bool esc;

		if (chapter == startseite) {
			p1.field_to_pixel(5, 17);
			p2.field_to_pixel(57, 17);

			p1.richtung = 1;
			p2.richtung = 2;

			winner = 0;

			for (int i = 0; i < 61; ++i) {
				for (int j = 0; j < 33; ++j)
				{
					kaestle[i][j] = frei;
				}
			}
			kaestle[3][16] = p1_feld;
			kaestle[57][16] = p2_feld;

			if (input().down(Gosu::KB_RETURN)) {
				chapter = spiel;
			}
		}

		if (chapter == spiel) {
			if (p1.richtung_alt == p1.richtung) {
				//Schalter von Player 1 abfragen
				if (input().down(Gosu::KB_D) & p1.richtung != 2) {
					p1.richtung = 1;
				}
				if (input().down(Gosu::KB_A) & p1.richtung != 1) {
					p1.richtung = 2;
				}
				if (input().down(Gosu::KB_W) & p1.richtung != 4) {
					p1.richtung = 3;
				}
				if (input().down(Gosu::KB_S) & p1.richtung != 3) {
					p1.richtung = 4;
				}
			}
			if (p2.richtung_alt == p2.richtung) {
				// Schalter von Player 2 abfragen
				if (input().down(Gosu::KB_RIGHT) & p2.richtung != 2) {
					p2.richtung = 1;
				}
				if (input().down(Gosu::KB_LEFT) & p2.richtung != 1) {
					p2.richtung = 2;
				}
				if (input().down(Gosu::KB_UP) & p2.richtung != 4) {
					p2.richtung = 3;
				}
				if (input().down(Gosu::KB_DOWN) & p2.richtung != 3) {
					p2.richtung = 4;
				}
				if (input().down(Gosu::KB_SPACE)) {
					chapter = ende;
				}
			}
			

			if (p1.in_grid==0) {		// Wenn p1 im Grid ist wird die richtung aktualisiert und das kaestle angemalt.
				p1.richtung_alt = p1.richtung;
				
				if (kaestle[(p1.pos_x - 46) / 30][(p1.pos_y - 46) / 30] == p2_spur) {
					chapter = ende;
					winner = 1;
				}
				if (kaestle[(p1.pos_x - 46) / 30][(p1.pos_y - 46) / 30] == p1_spur) {
					chapter = ende;
					winner = 2;
				}
				if (kaestle[(p1.pos_x - 46) / 30][(p1.pos_y - 46) / 30] == p2_feld) {
					kaestle[(p1.pos_x - 46) / 30][(p1.pos_y - 46) / 30] = p1_spur;
					p1.last_field_feld = false;
				}
				if (kaestle[(p1.pos_x - 46) / 30][(p1.pos_y - 46) / 30] == frei) {
					kaestle[(p1.pos_x - 46) / 30][(p1.pos_y - 46) / 30] = p1_spur;
					p1.last_field_feld = false;
				}
				if ((kaestle[(p1.pos_x - 46) / 30][(p1.pos_y - 46) / 30] == p1_feld) && p1.last_field_feld == false) {
					for (int i = 0; i < 61; ++i) {
						for (int j = 0; j < 33; ++j)
						{
							if (kaestle[i][j] == p1_spur) {
								kaestle[i][j] = p1_feld;
							}
						}
					}
					for (int i = 0; i < 61; ++i) {
						bool bereich=false;
						int j1 = 0, j2 = 0;
						int state = 0;
						for (int j = 0; j < 33; ++j)
						{
							if (kaestle[i][j] == p1_feld && bereich == false) {
								j1 = j;
								bereich = true;
							}
							if (kaestle[i][j] == p1_feld && bereich == true && state == 1) {
								j2 = j;
							}
							if (bereich == true && state == 0) {
								state = 1;
							}
							
						}
						for (int j = j1+1; j < j2; ++j)
						{
							if (kaestle[i][j] != p2_spur) {
								kaestle[i][j] = p1_feld;
							}
						}
					}
					p1.last_field_feld = true;
				}
				/*if (kaestle[(p1.pos_x - 46) / 30][(p1.pos_y - 46) / 30] == p1_feld) {			alte Versuchsversion (mit kleinem Bug)
					bool in_field = false;
					for (int i = 0; i < 61; ++i) {

						for (int j = 0; j < 33; ++j)
						{
							if (kaestle[i][j] == p1_feld) {
								in_field = false;
							}
							if (kaestle[i][j] == p1_spur && in_field == false) {
								in_field = true;
								if (kaestle[i][j-1] == p1_spur) {
									in_field = false;
								}
								kaestle[i][j] = p1_feld;
							}
							if (in_field == true) {
								if (kaestle[i][j] == p1_spur) {
									in_field = false;
								}
								kaestle[i][j] = p1_feld;
							}


						}
					}
				}*/
			}
			
			if (p2.in_grid==0) {		// Wenn p2 im Grid ist wird die richtung aktualisiert und das kaestle angemalt.
				p2.richtung_alt = p2.richtung;

				

				if (kaestle[(p2.pos_x - 46) / 30][(p2.pos_y - 46) / 30] == p1_spur) {
					chapter = ende;
					winner = 2;
				}
				if (kaestle[(p2.pos_x - 46) / 30][(p2.pos_y - 46) / 30] == p2_spur) {
					chapter = ende;
					winner = 1;
				}
				if (kaestle[(p2.pos_x - 46) / 30][(p2.pos_y - 46) / 30] == p1_feld) {
					kaestle[(p2.pos_x - 46) / 30][(p2.pos_y - 46) / 30] = p2_spur;
					p2.last_field_feld = false;
				}
				if (kaestle[(p2.pos_x - 46) / 30][(p2.pos_y - 46) / 30] == frei) {
					kaestle[(p2.pos_x - 46) / 30][(p2.pos_y - 46) / 30] = p2_spur;
					p2.last_field_feld = false;
				}
				if ((kaestle[(p2.pos_x - 46) / 30][(p2.pos_y - 46) / 30] == p2_feld) && p2.last_field_feld == false) {
					for (int i = 0; i < 61; ++i) {
						for (int j = 0; j < 33; ++j)
						{
							if (kaestle[i][j] == p2_spur) {
								kaestle[i][j] = p2_feld;
							}
						}
					}

					for (int i = 0; i < 61; ++i) {
						bool bereich = false;
						int j1 = 0, j2 = 0;
						int state = 0;
						for (int j = 0; j < 33; ++j)
						{
							if (kaestle[i][j] == p2_feld && bereich == false) {
								j1 = j;
								bereich = true;
							}
							if (kaestle[i][j] == p2_feld && bereich == true && state == 1) {
								j2 = j;
							}
							if (bereich == true && state == 0) {
								state = 1;
							}

						}
						for (int j = j1 + 1; j < j2; ++j)
						{
							if (kaestle[i][j] != p1_spur) {
								kaestle[i][j] = p2_feld;
							}
						}
					}
					p2.last_field_feld = true;
				}
				p2.score = 0;
				p1.score = 0;
				for (int i = 0; i < 61; ++i) {
					for (int j = 0; j < 33; ++j)
					{
						if (kaestle[i][j] == p2_feld) {
							p2.score = p2.score + 1;
						}
						if (kaestle[i][j] == p1_feld) {
							p1.score = p1.score + 1;
						}
					}
				}
				
				
				p1.score = p1.score * 100 / (33 * 61);
				p2.score = p2.score * 100 / (33 * 61);

				
				
				
				score_txt = "Player1: " + to_string(p1.score) + "%                    Player2: " + to_string(p2.score) + "%";
				
				//score_txt = score_string.str();
				
			}

			if (p1.fahren() == false) {	// Funktion "fahren()" in der class player aufrufen.
				chapter = ende;
				winner = 2;
			}
			if (p2.fahren() == false) {	// Funktion "fahren()" in der class player aufrufen.
				chapter = ende;
				winner = 1;
			}
			
		}

		if (chapter == ende) {
			if (input().down(Gosu::KB_ESCAPE)) {
				close();
			}
			if (input().down(Gosu::KB_RETURN)) {
				chapter = startseite;
			}
		}
			
	}


};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
