#pragma once

class Czlowiek {
public:
		int z;
		int y;
		int waga = 70;
		int cel;
		int poczatek;
		Czlowiek(int xx, int yy, int c, int p);
};

Czlowiek::Czlowiek(int xx, int yy, int c, int p) {
	z = xx;
	y = yy;
	cel = c;
	poczatek = p;
}