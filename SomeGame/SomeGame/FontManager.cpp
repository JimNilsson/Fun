#include "FontManager.h"

FontManager::FontManager()
{
}

FontManager::~FontManager()
{
	for (auto& font : _fonts)
		delete font.second;
}

sf::Font & FontManager::GetFont(const std::string & filename)
{
	auto exists = _fonts.find(filename);
	if (exists == _fonts.end())
	{
		_fonts[filename] = new sf::Font();
		if (!_fonts[filename]->loadFromFile(filename))
		{
			delete _fonts[filename];
			_fonts.erase(filename);
			throw std::exception(("Unable to load font " + filename).c_str());
		}
		return *(_fonts[filename]);
	}
	else
	{
		return *(exists->second);
	}
}
