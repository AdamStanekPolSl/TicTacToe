#include <SFML/Config.hpp>//korzystanie z biblioteki SFML
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Table.h"//do��czenie klasy Table, Field
#include "Field.h"

using namespace sf;//przestrze� nazw sfml
using namespace std;

int main()
{
	RenderWindow window(VideoMode(1280,720), "TicTacToe");//renderowanie okna gry
	window.setFramerateLimit(60);//limit klatek okina = 60/s
	window.setActive(1);// ustaw jako aktywne okno
	window.setVerticalSyncEnabled(1);//w��cz synchronizacj� pionow�
	window.setKeyRepeatEnabled(0);//wy��cz powtarzanie klawiszy


	Table table;//utw�rz tabel� gry
	Field field[3][3];//utw�rz pola gry
	for (int i{}; i < 3; i++)
	{
		for (int j{}; j < 3; j++)
		{
			field[i][j].setFieldPosition(i,j);//ustaw pola w odpowiednie miejsca na ekranie i przypisz im wsp�rz�dne (x,y) w tablicy
		}
	}


	while (window.isOpen())//gdy okno gry jest otwarte
	{
		Event e;//zdarzenie
		
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)//je�li zdarzenie == przycisk zamykania okna
				window.close();//zamknij okno gry = wyjd� z gry
		}
		window.clear(Color::White);//wype�nij okno biel�
		window.draw(table);//rysuj obiekt tabela w oknie gry(obrazek planszy)
		for (int i{}; i < 3; i++) //p�tla dla ka�dego pola (kolumna)
		{
			for (int j{}; j < 3; j++)//p�tla dla ka�dego pola (wiersz)
			{
				if (field[i][j].update(table.getFieldFromTable(i, j), table.getTurn(), window) != 0)//aktualizuje stany pola (patrz metoda Field::update()), "if" je�li na polu nast�pi�o przypisanie nowej warto�ci (wykonano ruch)
				{
					table.setPoints(table.update(i,j));//zaktualizuj stan planszy, sprawdza wygran� (przypisuje warto�� wygranej do zmiennej point)
				}
				window.draw(field[i][j]);//rysuj pole w oknie gry
			}
		}
		window.display();//wy�wietl okno gry
	}
}
