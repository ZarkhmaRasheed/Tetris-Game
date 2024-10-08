#pragma once
#include<iostream>
#include<sstream>
#include<string.h>
#include<time.h>
#include<vector>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
using namespace std;
class Game
{
private:
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::RenderTarget* target;
	sf::RectangleShape blocks[4];
	std::vector<sf::RectangleShape> block;
	sf::RectangleShape cell;
	sf::Clock clock;
	float cellspawntimer;
	float cellspawntimermax;
	int maxcells;
	int cell_size = 30;
	float x_pos;
	float y_pos;
	sf::Font font;
	sf::Text text;
	sf::Text text1;
	sf::Text text2;
	float fallTime;
	float deltaTime;
	void initWindow();
	bool createShape = true;
	bool isFalling = true;
	int randnum;
	std::string userName;
	int line;
	float elapsedTime;
	float updateInterval;
	sf::Clock clock1;
public:
	Game();
	void draws(sf::RectangleShape blocks[4]);
	void shapesoftetrimino();
	virtual ~Game();
	const bool running() const;
	void initfont();
	void windowcell();
	void checkCollision(sf::RectangleShape blocks[4]);
	void changeshape(sf::RectangleShape blocks[4], int randnumb);
	void pollEvents();
	void update();
	void render();
};
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<iostream>
#include<vector>
#include "Game.h"
#include<ctime>
#include <ctime>
#include <iostream>
#include <sstream>
#include <iomanip>
using namespace std;
void Game::initWindow()
{
	this->videoMode.height = 601;
	this->videoMode.width = 1200;
	this->window = new sf::RenderWindow(this->videoMode, "Tetris Game Designed By saqib ali", sf::Style::Titlebar | sf::Style::Close);
	this->cellspawntimer = 0.f;
	this->cellspawntimermax = 6000.f;
	this->maxcells = 5;
	this->fallTime = 1.f;
	this->deltaTime = clock.restart().asSeconds();
	this->fallTime -= deltaTime;
	this->elapsedTime = 0.0f;
	this->updateInterval = 1.0f; // Update line every 1 second
	this->elapsedTime += clock1.restart().asSeconds();
}
Game::Game()
{
	this->initWindow();
	this->initfont();
	this->windowcell();
}
Game::~Game()
{
	delete this->window;
}
const bool Game::running() const
{
	return this->window->isOpen();
}
void Game::initfont()
{
	if (!font.loadFromFile("fontfile.ttf"))
	{
		cout << "failed to load font file\n";
	}
	this->userName="Zarkhman";
	this->line = 0;
	this->text.setFont(this->font);
	this->text.setCharacterSize(40);
	this->text.setString("Player Name : "+userName);
	this->text.setPosition(310, 10);
	this->text.setFillColor(sf::Color::Black); //change
	this->window->draw(this->text);
	this->text1.setFont(this->font);
	this->text1.setCharacterSize(40);
	this->text1.setString("Lines : " +std::to_string(line));
	this->text1.setPosition(310, 100);
	this->text1.setFillColor(sf::Color::Black); //change
	this->window->draw(this->text1);
	//this->text2.setFont(this->font);
	//this->text2.setPosition(310, 200);
	//this->text2.setCharacterSize(40);
	//this->text2.setFillColor(sf::Color::White);
	//int seconds = 0;
	//std::stringstream ss;
	//seconds++;
	//	ss << "Time " << seconds;
	//	std::string lineStr = ss.str();
	//	this->text2.setString("Time : " + std::to_string(seconds));
	//	//this->text2.setString(lineStr);
	//	if (elapsedTime >= updateInterval)
	//	{
	//		seconds++;
	//		if (seconds > 60)
	//		{
	//			int minutes = seconds / 60;
	//			int remainingSeconds = seconds % 60;
	//			ss.str("");
	//			ss << "Line " << minutes << "m " << remainingSeconds << "s";
	//			//this->text2.setString(lineStr);
	//			this->text2.setString("Time : " + std::to_string(seconds));
	//			//this->window->draw(this->text2);
	//		}
	//		else
	//		{
	//			ss.str("");
	//			ss << "Line " << seconds << "s";f
	//			this->text2.setString("Time : " + std::to_string(seconds));
	//			this->window->draw(this->text2);
	//		}
	//		lineStr = ss.str();
	//		this->window->draw(this->text2);
	//		//this->elapsedTime = 0.0f; // Reset elapsed time
	//	}

	/*this->window->draw(this->text2);*/
}
void Game::windowcell()
{
	int x;
	int y = 0;
	for (int i = 1; i <= 20; i++)
	{
		x = 1;
		for (int j = 1; j <= 10; j++)
		{
			this->cell.setSize(sf::Vector2f(30, 30));
			this->cell.setFillColor(sf::Color::Black);
			this->cell.setPosition(x + 0.f, y + 0.f);
			this->cell.setOutlineColor(sf::Color::White);
			this->cell.setOutlineThickness(1.f);
			x = x + 30;
			this->window->draw(this->cell);
		}
		y = y + 30;
	}
}
void Game::changeshape(sf::RectangleShape blocks[4], int randnumb)
{
	if (randnumb == 1)// Z shape
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x, pivot.y + cell_size);
			blocks[2].setPosition(pivot.x + cell_size, pivot.y + cell_size);
			blocks[3].setPosition(pivot.x + cell_size, pivot.y + 2 * cell_size);
			// Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++)
			{
				this->window->draw(blocks[i]);
			}
		}
		if (event.key.code == sf::Keyboard::Space)
		{
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x - cell_size, pivot.y);
			blocks[2].setPosition(pivot.x + cell_size, pivot.y + cell_size);
			blocks[3].setPosition(pivot.x, pivot.y + cell_size);
			// Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++)
			{
				this->window->draw(blocks[i]);
			}
		}
	}
	else if (randnumb == 2) // L shape
	{
		if (this->event.key.code == sf::Keyboard::Up)
		{
			blocks[0].setPosition(0, 0);
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x - cell_size, pivot.y);
			blocks[2].setPosition(pivot.x + cell_size, pivot.y);
			blocks[3].setPosition(pivot.x + cell_size, pivot.y + cell_size);
			// Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++) {
				this->window->draw(blocks[i]);
			}
		}
		else if (event.key.code == sf::Keyboard::Space)
		{
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x, pivot.y - cell_size);
			blocks[2].setPosition(pivot.x, pivot.y + cell_size);
			blocks[3].setPosition(pivot.x + cell_size, pivot.y + cell_size);
			 //Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++)
			{
				this->window->draw(blocks[i]);
			}
		}
		else if (this->event.key.code == sf::Keyboard::Enter)
		{
			blocks[0].setPosition(0, 0);
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x + cell_size, pivot.y - cell_size);
			blocks[2].setPosition(pivot.x , pivot.y - cell_size);
			blocks[3].setPosition(pivot.x , pivot.y + cell_size);
			// Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++)
			{
				this->window->draw(blocks[i]);
			}
		}
		else if (this->event.key.code == sf::Keyboard::Slash)
		{
			blocks[0].setPosition(0, 0);
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x - cell_size, pivot.y - cell_size);
			blocks[2].setPosition(pivot.x - cell_size, pivot.y );
			blocks[3].setPosition(pivot.x + cell_size, pivot.y );
			// Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++)
			{
				this->window->draw(blocks[i]);
			}
		}
	}
	else if (randnumb == 3)// I shape
	{
		if (event.key.code == sf::Keyboard::Up)
		{
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x + cell_size, pivot.y);
			blocks[2].setPosition(pivot.x + cell_size + cell_size, pivot.y);
			blocks[3].setPosition(pivot.x + cell_size + cell_size + cell_size, pivot.y);
			// Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++)
			{
				this->window->draw(blocks[i]);
			}
		}
		if (event.key.code == sf::Keyboard::Space)
		{
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x, pivot.y + cell_size);
			blocks[2].setPosition(pivot.x, pivot.y + cell_size + cell_size);
			blocks[3].setPosition(pivot.x, pivot.y + cell_size + cell_size + cell_size);
			// Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++)
			{
				this->window->draw(blocks[i]);
			}
		}
	}
	else if (randnumb == 5)// T shape
	{
		if (event.key.code == sf::Keyboard::Up)
		{
		   sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
		   blocks[0].setPosition(pivot.x, pivot.y - cell_size);
		   blocks[2].setPosition(pivot.x + cell_size, pivot.y);
		   blocks[3].setPosition(pivot.x, pivot.y + cell_size);
        }
		else if (event.key.code == sf::Keyboard::Space)
		{
			sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			blocks[0].setPosition(pivot.x, pivot.y - cell_size);
			blocks[2].setPosition(pivot.x - cell_size, pivot.y);
			blocks[3].setPosition(pivot.x, pivot.y + cell_size);
			//Draw the L tetrimino on the game window
			for (int i = 0; i < 4; i++)
			{
				this->window->draw(blocks[i]);
			}
		}
		else if (event.key.code == sf::Keyboard::Slash)
		{
			 sf::Vector2f pivot;
			 pivot = blocks[1].getPosition(); // Use the second block as the pivot point
			 blocks[0].setPosition(pivot.x - cell_size, pivot.y);
			 blocks[2].setPosition(pivot.x + cell_size, pivot.y);
			 blocks[3].setPosition(pivot.x, pivot.y - cell_size);
		}
		else if (event.key.code == sf::Keyboard::Enter)
		{
		sf::Vector2f pivot;
		pivot = blocks[1].getPosition(); // Use the second block as the pivot point
		blocks[0].setPosition(pivot.x - cell_size, pivot.y);
		blocks[2].setPosition(pivot.x + cell_size, pivot.y);
		blocks[3].setPosition(pivot.x, pivot.y + cell_size);
		}
	}
}
void Game::draws(sf::RectangleShape blocks[4])
{
	if (this->fallTime <= 0.f)
	{
		this->blocks[0].move(0, 30);
		this->blocks[1].move(0, 30);
		this->blocks[2].move(0, 30);
		this->blocks[3].move(0, 30);
		this->fallTime = 1.f;// reset the timer
	}
	for (int i = 0; i < 4; i++)
	{
		this->window->draw(blocks[i]);
	}
	checkCollision(blocks);
	//if (blocks[2].getPosition().y >= 600)
	//{
	//	// move the tetromino back up
	//	blocks[0].move(0.f, -30.f);
	//	blocks[1].move(0.f, -30.f);
	//	blocks[2].move(0.f, -30.f);
	//	blocks[3].move(0.f, -30.f);
	//	// stop the tetromino
	//	blocks[0].setFillColor(sf::Color::Green);
	//	blocks[1].setFillColor(sf::Color::Green);
	//	blocks[2].setFillColor(sf::Color::Green);
	//	blocks[3].setFillColor(sf::Color::Green);
	//	createShape = true;
	//}
}
void Game::checkCollision(sf::RectangleShape blocks[4])
{
	// Check collision with the bottom of the window
	if (blocks[2].getPosition().y >= 600)
	{
		// move the tetromino back up
		blocks[0].move(0.f, -30.f);
		blocks[1].move(0.f, -30.f);
		blocks[2].move(0.f, -30.f);
		blocks[3].move(0.f, -30.f);
		// stop the tetromino
		blocks[0].setFillColor(sf::Color::Green);
		blocks[1].setFillColor(sf::Color::Green);
		blocks[2].setFillColor(sf::Color::Green);
		blocks[3].setFillColor(sf::Color::Green);
		createShape = true;
	}
	if ((blocks[3].getPosition().y + blocks[3].getSize().y) >= 604)
	{
		// Snap the block to the bottom of the window
		blocks[3].setPosition(blocks[3].getPosition().x, 604 - blocks[3].getSize().y);
		// Stop the tetromino from moving
		createShape = true;
	}
	// Add more collision checks here based on your game logic
}
void Game::shapesoftetrimino()
{
	this->randnum = rand() % 6;
	if (randnum == 1)
	{
		// Z shape
		this->blocks[0].setPosition(120, 0);
		this->blocks[1].setPosition(150, 0);
		this->blocks[2].setPosition(150, 30);
		this->blocks[3].setPosition(180, 30);
		for (int i = 0; i < 4; i++)
		{
			this->blocks[i].setSize(sf::Vector2f(cell_size, cell_size));
			this->blocks[i].setFillColor(sf::Color::Red);
			this->blocks[i].setOutlineColor(sf::Color::White);
			this->blocks[i].setOutlineThickness(1);
		}
		draws(blocks);
		changeshape(blocks, randnum);
	}
	else if (randnum == 2)
	{
		 //L shape 
		for (int i = 0; i < 4; i++)
		{
			this->blocks[i].setSize(sf::Vector2f(cell_size, cell_size));
			this->blocks[i].setFillColor(sf::Color::Magenta);
			this->blocks[i].setOutlineColor(sf::Color::White);
			this->blocks[i].setOutlineThickness(1);
		}
		this->blocks[0].setPosition(120, 0);
		this->blocks[1].setPosition(120, 30);
		this->blocks[2].setPosition(120, 60);
		this->blocks[3].setPosition(150, 60);
		draws(blocks);
		changeshape(blocks, randnum);
	}
	else if (randnum == 3)
	{
		// I shape 
		for (int i = 0; i < 4; i++)
		{
			this->blocks[i].setSize(sf::Vector2f(cell_size, cell_size));
			this->blocks[i].setFillColor(sf::Color::Blue);
			this->blocks[i].setOutlineColor(sf::Color::White);
			this->blocks[i].setOutlineThickness(1);
		}
		this->blocks[0].setPosition(120, 0);
		this->blocks[1].setPosition(120, 30);
		this->blocks[2].setPosition(120, 60);
		this->blocks[3].setPosition(120, 90);
		draws(blocks);
		changeshape(blocks, randnum);
	}
	else if (randnum == 4)
	{
		// O shape 
		for (int i = 0; i < 4; i++)
		{
			this->blocks[i].setSize(sf::Vector2f(cell_size, cell_size));
			this->blocks[i].setFillColor(sf::Color::Cyan);
			this->blocks[i].setOutlineColor(sf::Color::White);
			this->blocks[i].setOutlineThickness(1);
		}
		this->blocks[0].setPosition(120, 0);
		this->blocks[1].setPosition(150, 0);
		this->blocks[2].setPosition(120, 30);
		this->blocks[3].setPosition(150, 30);
		draws(blocks);
		changeshape(blocks, randnum);
	}
	else if (randnum == 5)
	{
		 //T shape
		for (int i = 0; i < 4; i++)
		{
			this->blocks[i].setSize(sf::Vector2f(cell_size, cell_size));
			this->blocks[i].setFillColor(sf::Color::Yellow);
			this->blocks[i].setOutlineColor(sf::Color::White);
			this->blocks[i].setOutlineThickness(1);
		}
		this->blocks[0].setPosition(120, 0);
		this->blocks[1].setPosition(150, 30);
		this->blocks[2].setPosition(180, 0);
		this->blocks[3].setPosition(150, 0);
		draws(blocks);
		changeshape(blocks, randnum);
	}
}
void Game::pollEvents()
{
	while (this->window->pollEvent(this->event))
	{
		if (this->event.key.code == sf::Keyboard::Escape)
			this->window->close();
		if (this->event.key.code == sf::Event::Closed)
			this->window->close();
		if (this->event.type == sf::Event::KeyPressed)
		{
			if (this->event.key.code == sf::Keyboard::Up)
			{
				//blocks[0].setPosition(0, 0);
				sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
				blocks[0].setPosition(pivot.x - cell_size, pivot.y);
				blocks[2].setPosition(pivot.x + cell_size, pivot.y);
				blocks[3].setPosition(pivot.x + cell_size, pivot.y + cell_size);
				// Draw the L tetrimino on the game window
				for (int i = 0; i < 4; i++)
				{
					this->window->draw(blocks[i]);
				}
			}
			if (event.key.code == sf::Keyboard::Space)
			{
				sf::Vector2f pivot = blocks[1].getPosition(); // Use the second block as the pivot point
				blocks[0].setPosition(pivot.x, pivot.y - cell_size);
				blocks[2].setPosition(pivot.x, pivot.y + cell_size);
				blocks[3].setPosition(pivot.x + cell_size, pivot.y + cell_size);
				// Draw the L tetrimino on the game window
				for (int i = 0; i < 4; i++)
				{
					this->window->draw(blocks[i]);
				}
			}
			 if (this->event.key.code == sf::Keyboard::Left)
			{
				// Move the shape of the block to the left side
				bool canMoveLeft = true;
				for (int i = 0; i < 4; i++)
				{
					if (this->blocks[i].getPosition().x < 30.0f)
						canMoveLeft = false;
				}
				if (canMoveLeft)
				{
					for (int i = 0; i < 4; i++)
						this->blocks[i].setPosition(this->blocks[i].getPosition().x - 30.0f, this->blocks[i].getPosition().y);
				}
			}
			else if (this->event.key.code == sf::Keyboard::Right)
			{
				// Move the shape of the block to the right side
				bool canMoveRight = true;
				for (int i = 0; i < 4; i++)
				{
					if (this->blocks[i].getPosition().x >= 270.0f)
						canMoveRight = false;
				}
				if (canMoveRight)
				{
					for (int i = 0; i < 4; i++)
						this->blocks[i].setPosition(this->blocks[i].getPosition().x + 30.0f, this->blocks[i].getPosition().y);
				}
			}
			else if (this->event.key.code == sf::Keyboard::Down)
			{
				//Move the shape of the block down faster
				 for (int i = 0; i < 4; i++)
				 this->blocks[i].setPosition(this->blocks[i].getPosition().x, this->blocks[i].getPosition().y + 30.0f);
			}
		}
	}
}
void Game::update()
{
	this->pollEvents();
}
void Game::render()
{
	this->window->clear(sf::Color::Green);
	this->windowcell();
	if (this->createShape)
	{
		this->shapesoftetrimino();
		this->createShape = false;
	}
	this->draws(blocks);
	this->changeshape(blocks, randnum);
	this->checkCollision(blocks);
	this->initfont();
	this->window->draw(this->text2);
	this->window->display();
	this->fallTime -= clock.restart().asSeconds();
	this->elapsedTime += clock1.restart().asSeconds();
}
#include<SFML/Graphics.hpp>
#include<SFML/System.hpp>
#include<SFML/Window.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<sstream>
#include<SFML/Graphics.hpp>
#include<ctime>
#include<iostream>
#include<sstream>
#include<iomanip>
#include<string.h>
#include<time.h>
#include<vector>
#include<Windows.h>
#include "Game.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics.hpp>
#include<SFML/Graphics.hpp>
#include<iostream>
#include<Windows.h>
#include "Game.h"
using namespace std;
int main()
{
    // game loop
    std::srand(static_cast<unsigned>(time(NULL)));
    Game game;
    while (game.running())
    {
        // update
        game.update();
        //render
        game.render();
    }
    return 0;
}
//const int WINDOW_WIDTH = 400;
//const int WINDOW_HEIGHT = 600;
//const int CELL_SIZE = 30;
//const int ARRAY_WIDTH = WINDOW_WIDTH / CELL_SIZE;
//const int ARRAY_HEIGHT = WINDOW_HEIGHT / CELL_SIZE;
//const int TETRIMINO_SIZE = 4;
//
//class TetrisGame {
//private:
//    sf::RenderWindow window;
//    sf::RectangleShape cell;
//    int gameArray[ARRAY_WIDTH][ARRAY_HEIGHT];
//
//public:
//    TetrisGame() {
//        initWindow();
//        initGameArray();
//        run();
//    }
//
//    void initWindow() {
//        window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Tetris Game");
//    }
//
//    void initGameArray() {
//        // Initialize game array with zeros
//        for (int i = 0; i < ARRAY_WIDTH; i++) {
//            for (int j = 0; j < ARRAY_HEIGHT; j++) {
//                gameArray[i][j] = 0;
//            }
//        }
//
//        // Set L-shaped tetrimino in the game array
//        int startX = ARRAY_WIDTH / 2;
//        int startY = 0;
//
//        // Set the L-shaped tetrimino in the top-left corner
//        for (int i = 0; i < TETRIMINO_SIZE; i++) {
//            gameArray[startX + i][startY] = 1;
//        }
//        gameArray[startX + TETRIMINO_SIZE - 1][startY + 1] = 1;
//    }
//
//    void drawTetrimino() {
//        for (int i = 0; i < ARRAY_WIDTH; i++) {
//            for (int j = 0; j < ARRAY_HEIGHT; j++) {
//                if (gameArray[i][j] == 1) {
//                    cell.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
//                    cell.setFillColor(sf::Color::Yellow);
//                    cell.setPosition(i * CELL_SIZE, j * CELL_SIZE);
//                    
//                    window.draw(cell);
//                }
//            }
//        }
//    }
//    void run() {
//        while (window.isOpen()) {
//            sf::Event event;
//            while (window.pollEvent(event)) {
//                if (event.type == sf::Event::Closed)
//                    window.close();
//            }
//            window.clear(sf::Color::Black);
//            // Update and draw game objects here
//            drawTetrimino();
//            window.display();
//        }
//    }
//};
//
//int main() {
//    TetrisGame game;
//
//    return 0;
//}
//

