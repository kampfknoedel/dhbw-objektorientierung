#include "stdafx.h"

#include <Gosu/Gosu.hpp>
#include <Gosu/AutoLink.hpp>

#include <vector>
#include <string>
#include <iostream>

#include "Vektor2d.h"

// Simulationsgeschwindigkeit
const double DT = 100.0;

class GameWindow : public Gosu::Window
{
public:
	Gosu::Image bild;
	GameWindow()
		: Window(1920, 1080, true)
	{
		set_caption("Gosu Tutorial Game mit Git");
	}

	// wird bis zu 60x pro Sekunde aufgerufen.
	// Wenn die Grafikkarte oder der Prozessor nicht mehr hinterherkommen,
	// dann werden `draw` Aufrufe ausgelassen und die Framerate sinkt
	void draw() override
	{
		// Notizen: Bildbereich: 1840x1000



		Gosu::Graphics::draw_rect(
			0, 0, 1920, 1080, Gosu::Color::GREEN,

			0.0
		);
		Gosu::Graphics::draw_rect(
			40, 40,	1840, 1000, Gosu::Color::BLACK,

			0.0
		);
		Gosu::Graphics::draw_rect(
			80, 80, 30, 30, Gosu::Color::RED,

			0.0
		);
	}

	// Wird 60x pro Sekunde aufgerufen
	void update() override
	{
	}
};

// C++ Hauptprogramm
int main()
{
	GameWindow window;
	window.show();
}
