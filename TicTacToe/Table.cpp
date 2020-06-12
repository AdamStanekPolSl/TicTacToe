#include "Table.h"

Table::Table()
{
    this->texture.loadFromFile("Assets/table.png");//wczytuje tekstur� z pliku
    this->sprite.setTexture(texture);//�aduje tekstur� do sprite (obrazka - obiektu w grze)
    sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);//ustawia o�, punkt zaczepienia na �rodek obrazka
    position.x = 640;//po�owa szeroko�ci rozdzielczo�ci (�rodek aplikacji na osi x)
    position.y = 360;// to samo dla y
    this->sprite.setPosition(position);//ustawia obrazek ("sprite") na �rodek ekranu
    this->reset();//wype�nia tablic� gry 0 - tablica jest pusta
    this->turn = 1;//krzy�yk zaczyna

    this->font.loadFromFile("Assets/ink-free.ttf");//wczytuje czcionk� z pliku

    this->crossPoints = 0;//ilo�� punkt�w = 0
    this->circlePoints = 0;// dla k�ka te�

    this->crossScore = to_string(crossPoints);//przechowuje int jako napis (string)
    this->circleScore = to_string(circlePoints);//dla k�ka te�

    Color blue(183, 234, 250,255);//kolorek niebieski (ilo�� czerwieni, ilo�� zieleni, ilo�� niebieskiego, moc "nieprzezroczysto�ci") warto�ci od 0 do 255
    Color red(250, 17, 0, 255);// czerwony

    this->crossText.setCharacterSize(120);//wielko�� liter
    this->crossText.setFont(font);//tekst b�dzie wy�wietlany czcionk�
    this->crossText.setString(crossScore);//ustawia napis do wy�wietlenia
    this->crossText.setPosition(1060, 140);// po�o�enie na ekranie (pobaw sie)
    this->crossText.setFillColor(red);//ustawia kolor napisu

    this->circleText.setCharacterSize(120);//jak wy�ej
    this->circleText.setFont(font);
    this->circleText.setString(circleScore);
    this->circleText.setPosition(1060, 370);
    this->circleText.setFillColor(blue);

}


void Table::reset()// resetuje tablic� do 0 (nowa gra)
{
    for (int i{}; i < 3; i++)//dla ka�dej kolumny
    {
        for (int j{}; j < 3; j++)//dla ka�dego wiersza
        {
            table[i][j] = 0;//konkretne pole w tablicy = 0
        }
    }
}


void Table::draw(RenderTarget& target, RenderStates state) const//nie rozumiem mechanizmu tej metody - rysuje "sprite"(obrazek), teksty(Text) w oknie (oknem jest RenderTarget), ta metoda przes�ania metod� draw w klasie Drawable (po kt�rej dziedzicz� nasze klasy)
{
    target.draw(this->sprite, state);
    target.draw(this->crossText, state);
    target.draw(this->circleText, state);
}


int Table::getTurn()//zwraca kto ma ruch
{
    return this->turn;// 1 = krzy�yk, -1 = k�ko
}


void Table::changeTurn()//zmienia ruch na drugiego gracza
{
    this->turn = turn*-1;
}


int Table::win()//sprawdza wygran�, remis
{
    Clock clock;//obiekt zegar - mierzy czas
    int horizontal{}, vertical{}, diagonalR{}, diagonalL{}, full{};//zmienne na wygrane w r�nych kierunkach, b�d� pe�n� plansz�
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
            if (this->table[j][j] == turn)//pod ukos w prawo(z g�ry na d�)
            {
                diagonalR++;
            }
            if (this->table[j][2 - j] == turn)//pod ukos w lewo
            {
                diagonalL++;
            }
            if (this->table[i][j] != 0)//pe�na plansza
            {
                full++;
            }
        }
        if (diagonalL == 3 || diagonalR == 3 || horizontal == 3 || vertical == 3)//gdy nast�pi�a wygrana
        {
            clock.restart();//wyzeruj sekundnik
            while (clock.getElapsedTime().asSeconds() < 1)//zeruj tablic� przez czas 1 s
                this->reset();
            return turn;//zwr�� kto wygra�
        }
        else if (full == 9)//gdy remis
        {
            clock.restart();//wyzeruj sekundnik
            while (clock.getElapsedTime().asSeconds() < 1)//przez sekund� zeruj tablic�
                this->reset();
        }
        else//gra si� toczy
        {
            diagonalL = 0;//zeruj warunki zwyci�stwa (brak mo�e spowodowa� obliczenie wygranej gdy nie nast�pi�a)
            diagonalR = 0;
            horizontal = 0;
            vertical = 0;
        }
    }
    full = 0;//zeruj warunek remisu
    changeTurn();//zmie� tur� gracza
    return 0;//zwr�� 0 - nikt nie wygra� w tym ruchu
}


int Table::getFieldFromTable(int x, int y)//zwraca warto�� konkretnego pola w tablicy (u�ywamy tego by przekaza� polu info jaki ma mie� stan(co ma wy�wietla� dane pole)
{
    return this->table[x][y];
}


int Table::update(int x, int y)// aktualizuje stan planszy (wpisuje do tablicy(x,y) odpowiedni� warto�� na skutek aktualizacji stan�w pola(x,y))
{
    this->table[x][y] = this->turn;//zmienia warto�� na odpowiadaj�c� postawionemu X lub O
    return this->win();//zwraca czy i kto wygra�, je�li nast�pi�a wygrana
}


void Table::setPoints(int point)//obs�uguje punkty
{
    if (point == 1)
        this->crossPoints++;//dodaje punkty X
    else if (point == -1)
        this->circlePoints++;//a to O
    if (crossPoints > 999 || circlePoints > 999)//zeruje wynik po osi�gnieciu 1000 pkt
    {
        crossPoints = 0;
        circlePoints = 0;
    }
    this->crossScore = to_string(crossPoints);//zaktualizuj napis
    this->circleScore = to_string(circlePoints);
    this->crossText.setString(crossScore);//zaktualizuj wy�wietlany tekst
    this->circleText.setString(circleScore);
}