#include "TextureManager.h"




sf::Texture & TextureManager::GetTexture(const std::string & filename)
{
	auto exists = _textureMap.find(filename);
	if (exists == _textureMap.end())
	{
		_textureMap[filename] = new sf::Texture();
		if (!_textureMap[filename]->loadFromFile(filename))
		{
			delete _textureMap[filename];
			_textureMap.erase(filename);
			throw std::exception(("Unable to load texture " + filename).c_str());
		}
		return *(_textureMap[filename]);
	}
	else
	{
		return *(exists->second);
	}
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for (auto& tex : _textureMap)
		delete tex.second;
}
