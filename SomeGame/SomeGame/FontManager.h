#ifndef _FONT_MANAGER_H_
#define _FONT_MANAGER_H_

#include <SFML\Graphics.hpp>
#include <unordered_map>

class FontManager
{
public:
	FontManager();
	~FontManager();

	sf::Font& GetFont(const std::string& filename);
private:
	std::unordered_map<std::string, sf::Font*> _fonts;

};

#endif
