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
    Table();//konstruktor obiektów klasy Table
    ~Table()//dekonstruktor obiektów klasy Table
    {}
    void reset();//resetuje tabele do stanu pocz¹tkowego
    void draw(RenderTarget& target, RenderStates state) const override;//rysuje obiekt w oknie
    int getTurn();//zwraca czyj ruch
    void changeTurn();//zmienia ruch na ruch drugiego gracza
    int update(int x, int y);//aktualizuje stan planszy, zwraca info kto wygra³ jeœli nast¹pi³a wygrana, x = kolumna, y = wiersz
    int win();//sprawdza wygran¹ - który gracz
    int getFieldFromTable(int x, int y);//zwraca wartoœæ pola
    void setPoints(int point);
private:
    Vector2f position;//ustala pozycjê tabeli
    Sprite sprite;//kszta³t do wyœwietlenia
    Texture texture;//tekstura
    Text crossText, circleText;//tekst do wyœwietlenia
    Font font;//czcionka
    string crossScore, circleScore;//napisy pod punkty
    int turn;//przechowuje informacjê "czyj ruch"
    int table[3][3];//stan planszy
    int crossPoints, circlePoints;//przechowuje punkty
};

