// Powtarzajacesiesymbole.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>


using namespace std;
const int MNOZNIK = 7;
const int DZIELNIK = 1035263;

class Pole
{
public:
	int kolor;
	int grupa;
};

class Grupa
{
public:
	int xmin, xmax, ymax, ymin;
	int hasz;
	int numer;
	void znajdzrozmiar(Pole **plansza, int szerokosc, int wysokosc)
	{
		xmin = szerokosc + 1;
		xmax = -1;
		ymin = wysokosc + 1;
		ymax = -1;

		for (int y = 0; y < wysokosc; y++)
		{
			for (int x = 0; x < szerokosc; x++)
			{
				//hasz *= MNOZNIK;
				if (plansza[y][x].grupa == numer)
				{
					if (x < xmin) {
						xmin = x;
					}
					if (x > xmax) {
						xmax = x;
					}
					if (y < ymin) {
						ymin = y;
					}
					if (y > ymax) {
						ymax = y;
					}
					//hasz += 1;
				}
				//hasz %= DZIELNIK;


			}
		}
	}
	void wypisz(Pole **plansza)
	{
		for (int y = ymin; y <= ymax; y++)
		{
			for (int x = xmin; x <= xmax; x++)
			{
				if (plansza[y][x].grupa == numer)
				{
					cout << 1;
				}
				else cout << 0;
			}
			cout << endl;
		}

	}
	void haszuj(Pole **plansza)
	{
		hasz = 0;
		for (int y = ymin; y <= ymax; y++)
		{
			for (int x = xmin; x <= xmax; x++)
			{
				hasz *= MNOZNIK;
				if (plansza[y][x].grupa == numer)
				{
					hasz += 1;;
				}
				hasz %= DZIELNIK;
			}
		}
	}
};
void DFS(Pole **plansza, int x, int y, int szerokosc, int wysokosc,int grupa)
{
	plansza[y][x].grupa = grupa; // przydzielamy do wybranej grupy
	int sasiadx, sasiady;
	//lewy sasiad
	sasiadx = x - 1;
	sasiady = y;
	if (sasiadx >= 0)
	{
		if (plansza[sasiady][sasiadx].kolor == 1 && plansza[sasiady][sasiadx].grupa == -1)
		{
			DFS(plansza,sasiadx, sasiady,szerokosc, wysokosc, grupa);
		}
	}
	//prawy sasiad
	sasiadx = x + 1;
	sasiady = y;
	if (sasiadx < szerokosc)
	{
		if (plansza[sasiady][sasiadx].kolor == 1 && plansza[sasiady][sasiadx].grupa == -1)
		{
			DFS(plansza, sasiadx, sasiady, szerokosc, wysokosc, grupa);
		}
	}
	//górny sasiad
	sasiadx = x ;
	sasiady = y -1;
	if (sasiady >= 0)
	{
		if (plansza[sasiady][sasiadx].kolor == 1 && plansza[sasiady][sasiadx].grupa == -1)
		{
			DFS(plansza, sasiadx, sasiady, szerokosc, wysokosc, grupa);
		}
	}
	//dolny sasiad
	sasiadx = x;
	sasiady = y +1;
	if (sasiady < wysokosc)
	{
		if (plansza[sasiady][sasiadx].kolor == 1 && plansza[sasiady][sasiadx].grupa == -1)
		{
			DFS(plansza, sasiadx, sasiady, szerokosc, wysokosc, grupa);
		}
	}
}
/*
int haszujgrupe(Pole **plansza, int szerokosc, int wysokosc, int nrgrupy)
{
	int hasz = 0;

	for (int y = 0; y < wysokosc; y++)
	{
		for (int x = 0; x < szerokosc; x++)
		{
			hasz *= MNOZNIK;
			if (plansza[y][x].grupa == nrgrupy)
			{
				hasz += 1;
				cout << "\t\t" << hasz << endl;
			}
			hasz %= DZIELNIK;


		}
	}
	cout << "\t\t\t" << hasz << endl;
	return hasz;
}
*/
int main()
{
	Pole ** plansza;
	int szer, wys;
	cin >> szer >> wys;

	plansza = new Pole*[wys];
	
	for (int i = 0; i < wys; i++)
	{
		plansza[i] = new Pole[szer];
	}
	char * bufor;
	bufor = new char[szer + 1]; // +1 informuje o koñcu tablicy

	for (int i = 0; i < wys; i++)
	{
		cin >> bufor;

		for (int j = 0; j < szer; j++)
		{
			plansza[i][j].grupa = -1; //zapewnienie ze nikt nie jest w zadnej grupie

			if (bufor[j] == '0' )
			{
				plansza[i][j].kolor = 0; // kolor bia³y
			}
			else
			{
				plansza[i][j].kolor = 1; // kolor czarny
			}
		}
	}
	//DFS(plansza,)
	int licznikgrupy = 0;
	for (int i = 0; i < wys; i++)
	{
		for (int j = 0; j < szer; j++)
		{
			if (plansza[i][j].kolor == 1 && plansza[i][j].grupa == -1)
			{
				DFS(plansza, j, i, szer, wys, licznikgrupy);
				licznikgrupy++;
			}
			
		}
	}
	/*
	for (int i = 0; i < wys; i++)
	{
		for (int j = 0; j < szer; j++) {
			cout << plansza[i][j].grupa<<'\t';
		}
		cout << endl;
	}
	*/
	
	int *licznikhaszy = new int[DZIELNIK];
	for (int i = 0; i < DZIELNIK; i++)
	{
		licznikhaszy[i] = 0;
	}
	Grupa* grupy;
	grupy = new Grupa[licznikgrupy];

	for (int i = 0; i < licznikgrupy; i++)
	{
		grupy[i].numer = i;
		grupy[i].znajdzrozmiar(plansza, szer, wys);
		grupy[i].haszuj(plansza);
		//int hasz = haszujgrupe(plansza, szer, wys, i);
		licznikhaszy[grupy[i].hasz]++;
	}
	int maksimum = -1;
	int najczestszyhasz = -1;
	for (int i = 0; i < DZIELNIK; i++)
	{

		if (licznikhaszy[i] > maksimum)
		{
			maksimum = licznikhaszy[i];
			najczestszyhasz = i;
		}
		
	}
	cout << maksimum << endl; 
	for (int i = 0; i < licznikgrupy; i++)
	{
		//cout << grupy[i].numer << " " << grupy[i].xmin << " " << grupy[i].ymin << " " << grupy[i].xmax << " " << grupy[i].ymax << " " << grupy[i].hasz << endl;
		
		if (grupy[i].hasz == najczestszyhasz)
		{
			grupy[i].wypisz(plansza);
			break;
		}
		
	}
	//cin >> szer;

    return 0;
}

