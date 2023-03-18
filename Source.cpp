#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "Header.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <deque>
#include <unordered_map>
#include <algorithm>
#include <time.h>

int main() {

	srand(time(NULL));

	sf::RenderWindow window(sf::VideoMode(1000, 800), "Snake");
	window.setKeyRepeatEnabled(false);

	std::deque<std::pair<int, int>> snake;
	std::pair<int, int> nextPos;
	std::pair<int, int> powerUp;
	generatePowerUps(powerUp);
	std::unordered_map<sf::Keyboard::Key, f> functions;

	functions[sf::Keyboard::Key::Down] = down;
	functions[sf::Keyboard::Key::Up] = up;
	functions[sf::Keyboard::Key::Left] = left;
	functions[sf::Keyboard::Key::Right] = right;

	sf::Keyboard::Key direction = sf::Keyboard::Key::Right;
	sf::Keyboard::Key prev_direction = sf::Keyboard::Key::Right;
	for (int i = 0; i < 200; i += 5) {
		snake.push_front({ i, 0 });
	}

	sf::Event event;
	sf::RectangleShape reckt(sf::Vector2f(5.f, 5.f));
	reckt.setFillColor(sf::Color::Red);
	while (window.isOpen()) {

		window.clear(sf::Color::Black);

		if (window.pollEvent(event)) {
			if (event.type == sf::Event::KeyPressed) {
				prev_direction = direction;
				direction = event.key.code;
			}
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		functions[direction](snake, nextPos);
		if (std::count(snake.begin(), snake.end(), nextPos)) {
			if (nextPos != *(snake.begin() + 1)) {
				window.close();			
			}
			else {
				direction = prev_direction;
				continue;
			}
		}

		if (nextPos.first <= powerUp.first + 10 && nextPos.first >= powerUp.first-4 && nextPos.second <= powerUp.second + 10 && nextPos.second >= powerUp.second-4) {
			snake.push_front(nextPos);
			generatePowerUps(powerUp);
		}
		else {
			snake.push_front(nextPos);
			snake.pop_back();
		}
		reckt.setSize(sf::Vector2f(5.f, 5.f));
		for (auto m : snake) {
			reckt.setPosition(sf::Vector2f(static_cast<float>(m.first), static_cast<float>(m.second)));
			window.draw(reckt);
		}
		reckt.setSize(sf::Vector2f(10.f, 10.f));
		reckt.setPosition(sf::Vector2f(static_cast<float>(powerUp.first), static_cast<float>(powerUp.second)));
		window.draw(reckt);
		window.display();
		std::this_thread::sleep_for(std::chrono::milliseconds(25));
	}
	sf::RenderWindow window2(sf::VideoMode(400, 400), "Kofti");
	sf::Font font;
	if (!font.loadFromFile("VHAVAN.ttf")) {
		std::cout << "couldn't load";
	}
	sf::Text text;
	text.setFont(font);
	text.setString("YOU ARE DEAD");
	text.setPosition(sf::Vector2f(40.f, 80.f));
	sf::Event event2;
	while (window2.isOpen()) {
		if (window2.pollEvent(event2)) {
			if (event2.type == sf::Event::Closed) {
				window2.close();
			}
		}
		window2.clear(sf::Color::Black);
		window2.draw(text);
		window2.display();
	}
	return 0;
}