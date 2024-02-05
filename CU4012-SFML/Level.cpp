#include "Level.h"

Level::Level(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	// initialise game objects
	// 
	//circle
	circle.setRadius(15);
	circle.setPosition(300, 300);
	circle.setFillColor(sf::Color::Green);
	circle.setOutlineColor(sf::Color::Magenta);
	circle.setOutlineThickness(2.f);

	speed = 200.f;

	//Player
	Player.setSize(sf::Vector2f(50, 50));
	Player.setFillColor(sf::Color::Red);
	Player.setOutlineThickness(5.f);
	Player.setPosition(100, 00);

	speed = 200.f;
	PlayerSpeed = 200.f;

	//Bouncing Shape
	bouncingShape.setRadius(20);
	bouncingShape.setPosition(150, 150);
	bouncingShape.setFillColor(sf::Color::Blue);
	bouncingShape.setOutlineColor(sf::Color::Blue);
	bouncingShape.setOutlineThickness(2.f);

	bouncingSpeedX = 200.f;
	bouncingSpeedY = 200.f;
}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	//Move Up
	if (input->isKeyDown(sf::Keyboard::W))
	{
		//input->setKeyUp(sf::Keyboard::W);
		Player.move(0, -PlayerSpeed * dt);
	}

	//Move Left
	if (input->isKeyDown(sf::Keyboard::A))
	{
		//input->setKeyUp(sf::Keyboard::A);
		Player.move(-PlayerSpeed *dt, 0);
	}

	//Moving Down
	if (input->isKeyDown(sf::Keyboard::S))
	{
		//input->setKeyUp(sf::Keyboard::S);
		Player.move(0, PlayerSpeed * dt);
	}
	//Moving Right
	if (input->isKeyDown(sf::Keyboard::D))
	{
		//input->setKeyUp(sf::Keyboard::D);
		Player.move(PlayerSpeed * dt, 0);
	}

	if (input->isKeyDown(sf::Keyboard::Add))
	{
		input->setKeyUp(sf::Keyboard::Add);

		bouncingSpeedX += 100;
		bouncingSpeedY += 100;
	}

	if (input->isKeyDown(sf::Keyboard::Subtract))
	{
		input->setKeyUp(sf::Keyboard::Subtract);

		bouncingSpeedX -= 100;
		bouncingSpeedY -= 100;
	}

	if (input->isKeyDown(sf::Keyboard::Add)) {
		input->setKeyUp(sf::Keyboard::Add);
		bouncingSpeedX += 100.f;
		bouncingSpeedY += 100.f;
	}
	if (input->isKeyDown(sf::Keyboard::Subtract)) {
		input->setKeyUp(sf::Keyboard::Subtract);
		bouncingSpeedX += 100.f;
		bouncingSpeedY += 100.f;
	}
}

// Update game objects
void Level::update(float dt)

{
	circle.move(speed * dt, 0);

	if (circle.getPosition().x <= window->getSize().x)
	{
		speed = speed;
	}
	else
		speed = -speed;

	 if (circle.getPosition().x <= 0)
	{
		 speed = -speed;
	}

	 //Boundary Checks For Player
	 sf::Vector2f pos = Player.getPosition();
	 sf::Vector2f size = Player.getSize();

	 //Right Boundary
	 if (pos.x > window->getSize().x - size.x) {
		 pos.x = window->getSize().x - size.x;
	 }

	 //Left Boundary
	 if (pos.x < 0) {
		 pos.x = 0;
	 }

	 //bottom boundary
	 if (pos.y > window->getSize().y - size.y) {
		 pos.y = window->getSize().y - size.y;
	 }

	 //top boundary
	 if (pos.y < 0) {
		 pos.y = 0;
	 }
	 // Apply corrected position
	 Player.setPosition(pos);

	 //Bouncing Logic
	 bouncingShape.move(bouncingSpeedX * dt, bouncingSpeedY * dt);

	 if (bouncingShape.getPosition().x <= 0 ||
		 bouncingShape.getPosition().x >= window->getSize().x - bouncingShape.getRadius() * 2) {
		 bouncingSpeedX = -bouncingSpeedX; 
	 }
	 if (bouncingShape.getPosition().y <= 0 ||
		 bouncingShape.getPosition().y >= window->getSize().y - bouncingShape.getRadius() * 2) {
		 bouncingSpeedY = -bouncingSpeedY;
	 }
}

// Render level
void Level::render()
{
	beginDraw();

	window->draw(circle);
	window->draw(Player);
	window->draw(bouncingShape);

	endDraw();
}

