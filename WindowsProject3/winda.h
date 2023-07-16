#pragma once
const int floor_distance = 120;

#include "czlowiek.h"
std::vector<Czlowiek> kolejkon[5];    //tablica z ludzmi
class Winda {
public:
	int pozycja = floor_distance*4;
	int pietro = 0;
	int status = 0; //0- wolna, 1- zajeta
	int cel = 0;
	std::vector<Czlowiek> ludzie;
	std::vector<int> przystanki{ 0 };
	std::vector<Czlowiek> srodek;
	void droga(int p, int c);
	void ruch();
	void wezwanie(Czlowiek czlowiek);
	bool chetni(int p);
	void stop(int p);
	void sprawdz();
	void reset();
	ULONGLONG licznik;
};

void Winda::reset() {
	if (licznik + 5000 < GetTickCount64() and przystanki.size() == 1) {
		droga(pietro, 0);
		pietro = 0;
	}
}

bool Winda::chetni(int p) {

	for (auto& man : kolejkon[p]) {
		for (int& drg : przystanki) {
			int tenid = man.id;
			if (man.cel == drg) {

				if (abs(man.z-man.zcel)>4 and srodek.size()<=7) {
					if (p % 2 == 0) {
						man.idz = 2;
						break;
					}
					else {
						man.idz = 1;
						break;
					}
				}
				else if (abs(man.z - man.zcel) > 4 and srodek.size() > 7) {
					if (p % 2 == 0) {
						man.idz = 0;
						man.z = man.z - 20;
						break;
					}
					else {
						man.idz = 0;
						man.z = man.z + 20;
						break;
					}
				}
				else {
					man.idz = 0;
					srodek.push_back(man);
					//kolejkon[p].erase(std::remove(kolejkon[p].begin(), kolejkon[p].end(), man),kolejkon[p].end());
					kolejkon[p].erase(std::remove_if(kolejkon[p].begin(), kolejkon[p].end(), [&](const Czlowiek& man) {
						return man.id == tenid;}),
						kolejkon[p].end()
							);
					ludzie.erase(std::remove_if(ludzie.begin(), ludzie.end(), [&](const Czlowiek& man) {
						return man.id == tenid;}),
						ludzie.end()
							);
					break;
				}
			}
		}
	}

	for (auto& man : srodek) {
		if (man.cel == p) {
			int tenid = man.id;
			if (abs(man.z-man.zcel2)>10) {
				if (p % 2 == 0) {
					man.idz = 1;
				}
				else {
					man.idz = 2;
				}
			}
			else {
				srodek.erase(std::remove_if(srodek.begin(), srodek.end(), [&](const Czlowiek& man) {
					return man.id == tenid;}),
					srodek.end()
						);
			}
		}
	}

	for (auto& man : kolejkon[p]) {
		if (man.idz != 0) return true;
	}
	for (auto& man : srodek) {
		if (man.idz != 0) return true;
	}
	return false;
}

void Winda::droga(int p, int c) {
	int i = pietro;
	while (i != p) {
		przystanki.push_back(i);
		if (i >= p) --i;
		else ++i;
	}
	while (i != c) {
		przystanki.push_back(i);
		if (i >= c) --i;
		else ++i;
	}
	przystanki.push_back(i);

}

void Winda::sprawdz() {
	pietro = przystanki[0];
	if (ludzie.empty()) {
		status = 0;
	}
	else {
		droga(ludzie[0].poczatek, ludzie[0].cel);
	}
}

void Winda::stop(int p) {


	if (przystanki.size() != 1) {

		przystanki.erase(przystanki.begin());
	}
	else if (przystanki.size() == 1) {
		sprawdz();
	}


}

void Winda::ruch() {
	if (srodek.size() > 8) {
		licznik = GetTickCount64();
	}
	else if ((pozycja) < (4 - (przystanki[0])) * floor_distance) {
		pozycja = pozycja + 2;
		licznik = GetTickCount64();
	}
	else if ((pozycja) > (4 - (przystanki[0])) * floor_distance) {
		pozycja = pozycja - 2;
		licznik = GetTickCount64();
	}
	else {
		if (chetni(przystanki[0])) {
			for (auto& man : kolejkon[przystanki[0]]) {
				if (man.idz == 1) {
					man.z = man.z - 2;
				}
				else if (man.idz == 2) {
					man.z = man.z + 2;
				}
			}
			for (auto& man : srodek) {
				if (man.idz == 1) {
					man.z = man.z - 2;
				}
				else if (man.idz == 2) {
					man.z = man.z + 2;
				}
			}
			licznik = GetTickCount64();
		}
		else {
			stop(przystanki[0]);
		}

	}
}


void Winda::wezwanie(Czlowiek czlowiek) {
	if (status == 0) {
		status = 1;
		droga(czlowiek.poczatek, czlowiek.cel);
	}
	else {
		ludzie.push_back(czlowiek);
	}
}

