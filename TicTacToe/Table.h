#pragma once
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;
using namespace std;

class Table :
    public Drawable
{
public:
    Table();//konstruktor obiekt�w klasy Table
    ~Table()//dekonstruktor obiekt�w klasy Table
    {}
    void reset();//resetuje tabele do stanu pocz�tkowego
    void draw(RenderTarget& target, RenderStates state) const override;//rysuje obiekt w oknie
    int getTurn();//zwraca czyj ruch
    void changeTurn();//zmienia ruch na ruch drugiego gracza
    int update(int x, int y);//aktualizuje stan planszy, zwraca info kto wygra� je�li nast�pi�a wygrana, x = kolumna, y = wiersz
    int win();//sprawdza wygran� - kt�ry gracz
    int getFieldFromTable(int x, int y);//zwraca warto�� pola
    void setPoints(int point);
private:
    Vector2f position;//ustala pozycj� tabeli
    Sprite sprite;//kszta�t do wy�wietlenia
    Texture texture;//tekstura
    Text crossText, circleText;//tekst do wy�wietlenia
    Font font;//czcionka
    string crossScore, circleScore;//napisy pod punkty
    int turn;//przechowuje informacj� "czyj ruch"
    int table[3][3];//stan planszy
    int crossPoints, circlePoints;//przechowuje punkty
};

