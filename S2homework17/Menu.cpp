#include "menu.h"

size_t Menu::getMaxItemSize() const
{
	size_t max = 0;
	for (std::string item : options)
	{
		if (item.size() > max) {
			max = item.size();
		}
	}
	return max;
}

size_t Menu::getFrameWidth() const
{
	return getMaxItemSize() + 6;
}

size_t Menu::getFrameHeight() const
{
	return options.size() + 4;
}

Menu::Menu(const std::vector<std::string>& options)
{
	this->options = options;
}

void Menu::drawFrame()
{
	size_t widht = getFrameWidth();
	size_t height = getFrameHeight();
	for (size_t y = 0; y < height; y++)
	{
		for (size_t x = 0; x < widht; x++)
		{
			if (x == 0 || x == widht - 1 || y == 0 || y == height - 1) {
				SetCursorPosition(x, y);
				SetColor(ConsoleColor::WHITE, ConsoleColor::TEAL_FADE);
				std::cout << ' ';
			}
		}
	}
	SetColor(WHITE, BLACK);
}

void Menu::drawOptions() 
{
	int startX = 3;
	int startY = 2;
	int max = getMaxItemSize();
	for (size_t i = 0; i < options.size(); i++)
	{
		SetCursorPosition(startX, startY + i);
		if (activeOption == i) 
		{
			SetColor(RED, WHITE);
		}
		else 
		{
			SetColor(WHITE, BLACK);
		}
		auto item = options[i];
		item.append(std::string(max - item.size(), ' '));
		std::cout << item;
	}
	SetColor(WHITE, BLACK);
}

void Menu::down() 
{
	activeOption++;
	if (activeOption >= options.size()) 
	{
		activeOption = 0;
	}
}

void Menu::up() 
{
	activeOption--;
	if (activeOption < 0) 
	{
		activeOption = options.size() - 1;
	}
}

int Menu::getSelectedOption() const 
{
	return activeOption;
}