#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "console.h"



class Menu {
private:
	int activeOption = 0;
	std::vector<std::string> options;
	size_t getMaxItemSize() const;
	size_t getFrameWidth() const;
	size_t getFrameHeight() const;
public:
	Menu(const std::vector<std::string>& options);
	Menu() {};
	void drawFrame();
	void drawOptions();
	void down();
	void up();
	int getSelectedOption() const;
};