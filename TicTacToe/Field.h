#pragma once
#include <SFML/Config.hpp>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;


class Field :
    public Drawable
{
public:
    Field();//konstruktor obiektów klasy Field
    ~Field()//dekonstruktor obiektów klasy Field
    {}
    void setFieldTexture(int value);//ustawia kó³ko/krzy¿yk/pust¹ texture na polu
    void setFieldPosition(int x, int y);//ustawia pozycjê pola oraz nadaje wspó³rzêdne = miejscu w tablicy
    void draw(RenderTarget& target, RenderStates state) const override;//wyœwietla pole w oknie
    int update(int value, int turn, Window &window);//aktualizuje stan pola, value = wartoœæ pola na planszy, turn = czyj ruch, window = okno gry
    bool mouseCollision(Window& window);//sprawdza czy myszka i pole siê przenikaj¹ (zwraca prawdê gdy kolizja)

private:
    Sprite sprite;//"fizyczny obiekt" pola, kszta³t na ekranie
    Texture cross, circle, none;//obrazek do wyœwietlenia
    int x, y;//wspó³rzêdne pola w tablicy
};

