#pragma once
#include <deque>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include <algorithm>
#pragma once
#include <deque>

int mod(int a, int b) { int ret = a % b; return ret >= 0 ? ret : ret + b; }

typedef void (*f)(std::deque<std::pair<int, int>>&, std::pair<int, int>&);

void left(std::deque<std::pair<int, int>>& janis, std::pair<int, int>& nextPos) {
	nextPos.first = mod(janis.front().first - 5, 1000);
	nextPos.second = janis.front().second;
}
void right(std::deque<std::pair<int, int>>& janis, std::pair<int, int>& nextPos) {
	nextPos.first = mod(janis.front().first + 5, 1000);
	nextPos.second = janis.front().second;
}
void up(std::deque<std::pair<int, int>>& janis, std::pair<int, int>& nextPos) {
	nextPos.first = janis.front().first;
	nextPos.second = mod(janis.front().second - 5, 800);
}
void down(std::deque<std::pair<int, int>>& janis, std::pair<int, int>& nextPos) {
	nextPos.first = janis.front().first;
	nextPos.second = mod(janis.front().second + 5, 800);
}

void generatePowerUps(std::pair<int, int>& queso) {
	queso.first = rand() % 990;
	queso.second = rand() % 790;
}