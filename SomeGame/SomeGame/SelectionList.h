#ifndef _SELECTION_LIST_H_
#define _SELECTION_LIST_H_

#include <SFML\Graphics.hpp>
#include <vector>
#include <functional>

class SelectionList : public sf::Drawable
{
public:
	SelectionList(sf::Vector2f position = sf::Vector2f(0,0), const std::string& fontname = "Fonts/arial.ttf");
	~SelectionList();

	void SetFont(const std::string& fontname);
	void SetPosition(const sf::Vector2f& pos);
	void CenterOnPos(bool enable = true);
	void CenterItems(bool enable = true);
	
	void SetSpacing(int width);

	void AddOption(const std::string& text, std::function<void()> callback = nullptr);

	int Update();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	struct Item
	{
		sf::Text text;
		std::function<void()> callback;
	};
	std::string _fontname;
	sf::Vector2f _position;
	std::vector<Item> _items;
	int _selectedItem = 0;
	unsigned _distanceBetweenItems;
	sf::Color _selectionColor;
	sf::Color _unselectedColor;
	bool _centerOnPos = false;
	bool _centerItems = false;


	float _Height(int firstXElements = -1);
	void _Reposition();
	void _Center();
	void _CenterItems();

};


#endif

