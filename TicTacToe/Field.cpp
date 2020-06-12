#include "Field.h"

Field::Field()
{
	this->cross.loadFromFile("Assets/Cross.png");//wczytywanie tekstur z pliku
	this->circle.loadFromFile("Assets/Circle.png");
	this->none.loadFromFile("Assets/None.png");
}


void Field::setFieldTexture(int value)
{
	if (value == 1)
		sprite.setTexture(cross);//przypisz krzy�yk polu
	else if (value == -1)
		sprite.setTexture(circle);//k�ko
	else
		sprite.setTexture(none);//nic
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);//ustaw o� (punkt zaczepienia, obrotu itd.) kszta�tu do wy�wietlania na �rodek obrazka (1/2 szer., 1/2 wys)
}


int Field::update(int value, int turn, Window &window)//value = warto�� pola w  tablicy, turn = kto ma ruch, window = okno gry
{
	if (value == 0 && this->mouseCollision(window))//gdy pole jest puste i najazd myszk�
	{
		this->setFieldTexture(turn);//ustaw obrazek aktualnego gracza
		if (Mouse::isButtonPressed(Mouse::Left))//je�li dodatkowo klik 
			return turn;//zwr�� warto�� przypisan� obecnemu graczowi
		else
			return 0;//zwr�� warto�� 0 (0 = pomini�cie aktualizacji danych w tablicy gry)
	}
	else// gdy nie puste lub nie najazd myszk�
	{
		this->setFieldTexture(value);//wy�wietl obrazek odpowiadaj�cy warto�ci pola w tablicy
		return 0;//zwr�� warto�� 0 (0 = pomini�cie aktualizacji danych w tablicy gry)
	}
}


void Field::setFieldPosition(int x, int y)//ustawia pozycj� pola oraz nadaje wsp�rz�dne = miejscu w tablicy
{
	this->x = x;//this->pokazuje na zmienn� x nale��c� do obiektu tej klasy, przypisuje x przekazane w argumencie metody
	this->y = y;//to samo dla y
	this->sprite.setPosition((125 + (234 * x)), (125 + (234 * y)));//zabawy z pikselami(numer pola daje nam odpowiedni� lokalizacj�)
}


void Field::draw(RenderTarget& target, RenderStates state) const//nie rozumiem mechanizmu tej metody - rysuje "sprite"(obrazek) w oknie (oknem jest RenderTarget), ta metoda przes�ania metod� draw w klasie Drawable (po kt�rej dziedzicz� nasze klasy)
{
	target.draw(this->sprite, state);
}


bool Field::mouseCollision(Window &window)//zwraca prawd� je�li myszka najecha�a na pole
{
	if (Mouse::getPosition(window).x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) &&//wsp�rz�dna x myszy jest < prawej strony pola
		Mouse::getPosition(window).x > sprite.getGlobalBounds().left &&//wsp�rz�dna x myszy jest > lewej strony pola
		Mouse::getPosition(window).y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) &&//wsp�rz�dna y myszy jest < dolnej strony pola
		Mouse::getPosition(window).y > sprite.getGlobalBounds().top)//wsp�rz�dna y myszy jest > g�rnej strony pola
		return true;
	else
		return false;
}