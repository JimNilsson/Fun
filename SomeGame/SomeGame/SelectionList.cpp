#include "SelectionList.h"
#include "Application.h"
#include <iostream>
#include <algorithm>

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

void SelectionList::SetPosition(const sf::Vector2f & pos)
{
	_position = pos;
	_Reposition();
}

void SelectionList::CenterOnPos(bool enable)
{
	_centerOnPos = enable;
	_Reposition();
}

void SelectionList::CenterItems(bool enable)
{
	_centerItems = true;
	_Reposition();
}

void SelectionList::_Center()
{
	float maxWidth = 0.0f;
	for (auto& item : _items)
	{
		maxWidth = std::max(item.text.getGlobalBounds().width, maxWidth);
	}
	maxWidth /= 2.0f;
	float height = _Height() / 2.0f;
	for (auto& item : _items)
	{
		item.text.move({ -maxWidth, -height });
	}
}

void SelectionList::_CenterItems()
{
	float maxWidth = 0.0f;
	for (auto& item : _items)
	{
		maxWidth = std::max(item.text.getGlobalBounds().width, maxWidth);
	}
	
	for (auto& item : _items)
	{
		item.text.move({ (maxWidth - item.text.getGlobalBounds().width) / 2.0f, 0.0f });
	}


}

void SelectionList::SetSpacing(int width)
{
	_distanceBetweenItems = width;
	_Reposition();
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
	_Reposition();
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

float SelectionList::_Height(int firstXElements)
{
	if (firstXElements < 0)
		firstXElements = _items.size();
	float height = 0.0f;
	for (int i = 0; i < firstXElements; i++)
		height += _items[i].text.getGlobalBounds().height + _distanceBetweenItems;
	return height;
}

void SelectionList::_Reposition()
{
	int i = 0;
	for (auto& item : _items)
	{
		item.text.setPosition({ _position.x, _position.y + _Height(i) });
		i++;
	}

	if (_centerOnPos)
		_Center();
	if (_centerItems)
		_CenterItems();
}

