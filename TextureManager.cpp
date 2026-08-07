#include "TextureManager.h"

TextureManager::TextureManager() {}

TextureManager& TextureManager::getInstance() {
    static TextureManager instance;
    return instance;
}

bool TextureManager::loadTexture(const std::string& id, const std::string& filename) {
    sf::Texture texture;
    if (!texture.loadFromFile(filename)) {
        return false; // Failed to load texture
        textures[id] = texture;
        return true;
    }
}
sf::Texture& TextureManager::getTexture(const std::string& id) {
    return textures.at(id);
}