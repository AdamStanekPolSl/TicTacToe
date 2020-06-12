#pragma once
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class Field :
    public Drawable
{
public:
    Field();//konstruktor obiekt�w klasy Field
    ~Field()//dekonstruktor obiekt�w klasy Field
    {}
    void setFieldTexture(int value);//ustawia k�ko/krzy�yk/pust� texture na polu
    void setFieldPosition(int x, int y);//ustawia pozycj� pola oraz nadaje wsp�rz�dne = miejscu w tablicy
    void draw(RenderTarget& target, RenderStates state) const override;//wy�wietla pole w oknie
    int update(int value, int turn, Window &window);//aktualizuje stan pola, value = warto�� pola na planszy, turn = czyj ruch, window = okno gry
    bool mouseCollision(Window& window);//sprawdza czy myszka i pole si� przenikaj� (zwraca prawd� gdy kolizja)

private:
    Sprite sprite;//"fizyczny obiekt" pola, kszta�t na ekranie
    Texture cross, circle, none;//obrazek do wy�wietlenia
    int x, y;//wsp�rz�dne pola w tablicy
};

