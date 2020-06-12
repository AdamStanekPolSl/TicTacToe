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
		sprite.setTexture(cross);//przypisz krzy¿yk polu
	else if (value == -1)
		sprite.setTexture(circle);//kó³ko
	else
		sprite.setTexture(none);//nic
	sprite.setOrigin(sprite.getGlobalBounds().width / 2.f, sprite.getGlobalBounds().height / 2.f);//ustaw oœ (punkt zaczepienia, obrotu itd.) kszta³tu do wyœwietlania na œrodek obrazka (1/2 szer., 1/2 wys)
}


int Field::update(int value, int turn, Window &window)//value = wartoœæ pola w  tablicy, turn = kto ma ruch, window = okno gry
{
	if (value == 0 && this->mouseCollision(window))//gdy pole jest puste i najazd myszk¹
	{
		this->setFieldTexture(turn);//ustaw obrazek aktualnego gracza
		if (Mouse::isButtonPressed(Mouse::Left))//jeœli dodatkowo klik 
			return turn;//zwróæ wartoœæ przypisan¹ obecnemu graczowi
		else
			return 0;//zwróæ wartoœæ 0 (0 = pominiêcie aktualizacji danych w tablicy gry)
	}
	else// gdy nie puste lub nie najazd myszk¹
	{
		this->setFieldTexture(value);//wyœwietl obrazek odpowiadaj¹cy wartoœci pola w tablicy
		return 0;//zwróæ wartoœæ 0 (0 = pominiêcie aktualizacji danych w tablicy gry)
	}
}


void Field::setFieldPosition(int x, int y)//ustawia pozycjê pola oraz nadaje wspó³rzêdne = miejscu w tablicy
{
	this->x = x;//this->pokazuje na zmienn¹ x nale¿¹c¹ do obiektu tej klasy, przypisuje x przekazane w argumencie metody
	this->y = y;//to samo dla y
	this->sprite.setPosition((125 + (234 * x)), (125 + (234 * y)));//zabawy z pikselami(numer pola daje nam odpowiedni¹ lokalizacjê)
}


void Field::draw(RenderTarget& target, RenderStates state) const//nie rozumiem mechanizmu tej metody - rysuje "sprite"(obrazek) w oknie (oknem jest RenderTarget), ta metoda przes³ania metodê draw w klasie Drawable (po której dziedzicz¹ nasze klasy)
{
	target.draw(this->sprite, state);
}


bool Field::mouseCollision(Window &window)//zwraca prawdê jeœli myszka najecha³a na pole
{
	if (Mouse::getPosition(window).x < (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width) &&//wspó³rzêdna x myszy jest < prawej strony pola
		Mouse::getPosition(window).x > sprite.getGlobalBounds().left &&//wspó³rzêdna x myszy jest > lewej strony pola
		Mouse::getPosition(window).y < (sprite.getGlobalBounds().top + sprite.getGlobalBounds().height) &&//wspó³rzêdna y myszy jest < dolnej strony pola
		Mouse::getPosition(window).y > sprite.getGlobalBounds().top)//wspó³rzêdna y myszy jest > górnej strony pola
		return true;
	else
		return false;
}