#include "SelectionList.h"
#include "Application.h"
#include <iostream>

SelectionList::SelectionList(sf::Vector2f position, const std::string& fontname)
{
	_position = position;
	_fontname = fontname;

	_selectionColor = sf::Color::Yellow;
	_unselectedColor = sf::Color::White;
	_distanceBetweenItems = 5;
}

SelectionList::~SelectionList()
{
}

void SelectionList::SetFont(const std::string& fontname)
{
	_fontname = fontname;
	sf::Font& font = Application::GetInstance()->Fonts()->GetFont(fontname);
	for (auto& item : _items)
		item.text.setFont(font);
}

void SelectionList::AddOption(const std::string & text, std::function<void()> callback)
{
	float height = _Height();
	_items.push_back(Item());
	sf::Font& font = Application::GetInstance()->Fonts()->GetFont(_fontname);
	_items.back().text.setFont(font);
	_items.back().text.setString(text);
	_items.back().text.setPosition(_position + sf::Vector2f(0, height));
	_items.back().callback = callback;
}

int SelectionList::Update()
{
	for (auto& item : _items)
	{
		item.text.setFillColor(sf::Color::White);
	}
	EventHandler* events = Application::GetInstance()->Events();
	if (events->KeySinglePress(sf::Keyboard::Return))
	{
		if (_items[_selectedItem].callback != nullptr)
		{
			(_items[_selectedItem]).callback();
		}	
	}

	if (events->KeySinglePress(sf::Keyboard::Down))
		_selectedItem = (_selectedItem + 1) % _items.size();
	if(events->KeySinglePress(sf::Keyboard::Up))
		_selectedItem = (_selectedItem + _items.size() - 1) % _items.size();

	_items[_selectedItem].text.setFillColor(sf::Color::Yellow);

	return 0;
}

void SelectionList::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (auto& item : _items)
	{
		target.draw(item.text);
	}
}

float SelectionList::_Height()
{
	float height = 0.0f;
	for (auto& item : _items)
		height += item.text.getGlobalBounds().height + _distanceBetweenItems;
	return height;
}
