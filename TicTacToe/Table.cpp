#include "Table.h"

Table::Table()
{
    this->texture.loadFromFile("Assets/table.png");//wczytuje teksturê z pliku
    this->sprite.setTexture(texture);//³aduje teksturê do sprite (obrazka - obiektu w grze)
    sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);//ustawia oœ, punkt zaczepienia na œrodek obrazka
    position.x = 640;//po³owa szerokoœci rozdzielczoœci (œrodek aplikacji na osi x)
    position.y = 360;// to samo dla y
    this->sprite.setPosition(position);//ustawia obrazek ("sprite") na œrodek ekranu
    this->reset();//wype³nia tablicê gry 0 - tablica jest pusta
    this->turn = 1;//krzy¿yk zaczyna

    this->font.loadFromFile("Assets/ink-free.ttf");//wczytuje czcionkê z pliku

    this->crossPoints = 0;//iloœæ punktów = 0
    this->circlePoints = 0;// dla kó³ka te¿

    this->crossScore = to_string(crossPoints);//przechowuje int jako napis (string)
    this->circleScore = to_string(circlePoints);//dla kó³ka te¿

    Color blue(183, 234, 250,255);//kolorek niebieski (iloœæ czerwieni, iloœæ zieleni, iloœæ niebieskiego, moc "nieprzezroczystoœci") wartoœci od 0 do 255
    Color red(250, 17, 0, 255);// czerwony

    this->crossText.setCharacterSize(120);//wielkoœæ liter
    this->crossText.setFont(font);//tekst bêdzie wyœwietlany czcionk¹
    this->crossText.setString(crossScore);//ustawia napis do wyœwietlenia
    this->crossText.setPosition(1060, 140);// po³o¿enie na ekranie (pobaw sie)
    this->crossText.setFillColor(red);//ustawia kolor napisu

    this->circleText.setCharacterSize(120);//jak wy¿ej
    this->circleText.setFont(font);
    this->circleText.setString(circleScore);
    this->circleText.setPosition(1060, 370);
    this->circleText.setFillColor(blue);

}


void Table::reset()// resetuje tablicê do 0 (nowa gra)
{
    for (int i{}; i < 3; i++)//dla ka¿dej kolumny
    {
        for (int j{}; j < 3; j++)//dla ka¿dego wiersza
        {
            table[i][j] = 0;//konkretne pole w tablicy = 0
        }
    }
}


void Table::draw(RenderTarget& target, RenderStates state) const//nie rozumiem mechanizmu tej metody - rysuje "sprite"(obrazek), teksty(Text) w oknie (oknem jest RenderTarget), ta metoda przes³ania metodê draw w klasie Drawable (po której dziedzicz¹ nasze klasy)
{
    target.draw(this->sprite, state);
    target.draw(this->crossText, state);
    target.draw(this->circleText, state);
}


int Table::getTurn()//zwraca kto ma ruch
{
    return this->turn;// 1 = krzy¿yk, -1 = kó³ko
}


void Table::changeTurn()//zmienia ruch na drugiego gracza
{
    this->turn = turn*-1;
}


int Table::win()//sprawdza wygran¹, remis
{
    Clock clock;//obiekt zegar - mierzy czas
    int horizontal{}, vertical{}, diagonalR{}, diagonalL{}, full{};//zmienne na wygrane w ró¿nych kierunkach, b¹dŸ pe³n¹ planszê
    for (int i{}; i < 3; i++)
    {
        for (int j{}; j < 3; j++)
        {
            if (this->table[i][j] == turn)//pionowo x3
            {
                vertical++;
            }
            if (this->table[j][i] == turn)//poziomo x3
            {
                horizontal++;
            }
            if (this->table[j][j] == turn)//pod ukos w prawo(z góry na dó³)
            {
                diagonalR++;
            }
            if (this->table[j][2 - j] == turn)//pod ukos w lewo
            {
                diagonalL++;
            }
            if (this->table[i][j] != 0)//pe³na plansza
            {
                full++;
            }
        }
        if (diagonalL == 3 || diagonalR == 3 || horizontal == 3 || vertical == 3)//gdy nast¹pi³a wygrana
        {
            clock.restart();//wyzeruj sekundnik
            while (clock.getElapsedTime().asSeconds() < 1)//zeruj tablicê przez czas 1 s
                this->reset();
            return turn;//zwróæ kto wygra³
        }
        else if (full == 9)//gdy remis
        {
            clock.restart();//wyzeruj sekundnik
            while (clock.getElapsedTime().asSeconds() < 1)//przez sekundê zeruj tablicê
                this->reset();
        }
        else//gra siê toczy
        {
            diagonalL = 0;//zeruj warunki zwyciêstwa (brak mo¿e spowodowaæ obliczenie wygranej gdy nie nast¹pi³a)
            diagonalR = 0;
            horizontal = 0;
            vertical = 0;
        }
    }
    full = 0;//zeruj warunek remisu
    changeTurn();//zmieñ turê gracza
    return 0;//zwróæ 0 - nikt nie wygra³ w tym ruchu
}


int Table::getFieldFromTable(int x, int y)//zwraca wartoœæ konkretnego pola w tablicy (u¿ywamy tego by przekazaæ polu info jaki ma mieæ stan(co ma wyœwietlaæ dane pole)
{
    return this->table[x][y];
}


int Table::update(int x, int y)// aktualizuje stan planszy (wpisuje do tablicy(x,y) odpowiedni¹ wartoœæ na skutek aktualizacji stanów pola(x,y))
{
    this->table[x][y] = this->turn;//zmienia wartoœæ na odpowiadaj¹c¹ postawionemu X lub O
    return this->win();//zwraca czy i kto wygra³, jeœli nast¹pi³a wygrana
}


void Table::setPoints(int point)//obs³uguje punkty
{
    if (point == 1)
        this->crossPoints++;//dodaje punkty X
    else if (point == -1)
        this->circlePoints++;//a to O
    if (crossPoints > 999 || circlePoints > 999)//zeruje wynik po osi¹gnieciu 1000 pkt
    {
        crossPoints = 0;
        circlePoints = 0;
    }
    this->crossScore = to_string(crossPoints);//zaktualizuj napis
    this->circleScore = to_string(circlePoints);
    this->crossText.setString(crossScore);//zaktualizuj wyœwietlany tekst
    this->circleText.setString(circleScore);
}