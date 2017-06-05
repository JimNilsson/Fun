#ifndef _TEXTURE_MANAGER_H_
#define _TEXTURE_MANAGER_H_

#include <SFML\Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	sf::Texture& GetTexture(const std::string& filename);
private:

	std::unordered_map<std::string, sf::Texture*> _textureMap;
	
};


#endif
