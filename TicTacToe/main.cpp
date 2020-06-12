#include <SFML/Config.hpp>//korzystanie z biblioteki SFML
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Table.h"//do³¹czenie klasy Table, Field
#include "Field.h"

using namespace sf;//przestrzeñ nazw sfml
using namespace std;

int main()
{
	RenderWindow window(VideoMode(1280,720), "TicTacToe");//renderowanie okna gry
	window.setFramerateLimit(60);//limit klatek okina = 60/s
	window.setActive(1);// ustaw jako aktywne okno
	window.setVerticalSyncEnabled(1);//w³¹cz synchronizacjê pionow¹
	window.setKeyRepeatEnabled(0);//wy³¹cz powtarzanie klawiszy


	Table table;//utwórz tabelê gry
	Field field[3][3];//utwórz pola gry
	for (int i{}; i < 3; i++)
	{
		for (int j{}; j < 3; j++)
		{
			field[i][j].setFieldPosition(i,j);//ustaw pola w odpowiednie miejsca na ekranie i przypisz im wspó³rzêdne (x,y) w tablicy
		}
	}


	while (window.isOpen())//gdy okno gry jest otwarte
	{
		Event e;//zdarzenie
		
		while (window.pollEvent(e))
		{
			if (e.type == Event::Closed)//jeœli zdarzenie == przycisk zamykania okna
				window.close();//zamknij okno gry = wyjdŸ z gry
		}
		window.clear(Color::White);//wype³nij okno biel¹
		window.draw(table);//rysuj obiekt tabela w oknie gry(obrazek planszy)
		for (int i{}; i < 3; i++) //pêtla dla ka¿dego pola (kolumna)
		{
			for (int j{}; j < 3; j++)//pêtla dla ka¿dego pola (wiersz)
			{
				if (field[i][j].update(table.getFieldFromTable(i, j), table.getTurn(), window) != 0)//aktualizuje stany pola (patrz metoda Field::update()), "if" jeœli na polu nast¹pi³o przypisanie nowej wartoœci (wykonano ruch)
				{
					table.setPoints(table.update(i,j));//zaktualizuj stan planszy, sprawdza wygran¹ (przypisuje wartoœæ wygranej do zmiennej point)
				}
				window.draw(field[i][j]);//rysuj pole w oknie gry
			}
		}
		window.display();//wyœwietl okno gry
	}
}
