#pragma once

class Czlowiek {
public:
		int z;
		int zcel;
		int zcel2;
		int y;
		int cel;
		int poczatek;
		int id;
		int idz = 0; //0- stoj, 1- lewo, 2- prawo
		Czlowiek(int xx, int yy, int c, int p, int d);
		int cel1(int xx);
		int cel2();
};

int Czlowiek::cel1(int xx) {
	if (poczatek % 2 == 0) {
		return xx + 210;
	}
	else {
		return xx - 300;
	}
}
int Czlowiek::cel2() {
	if (cel % 2 == 0) {
		return 0;
	}
	else {
		return 700;
	}

}
Czlowiek::Czlowiek(int xx, int yy, int c, int p, int d) {
	z = xx;
	y = yy;
	cel = c;
	poczatek = p;
	id = d;
	zcel = cel1(xx);
	zcel2 = cel2();
}