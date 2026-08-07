#include "AssetManager.h"

#include <SFML/Graphics/Image.hpp>
#include <iostream>

namespace {

bool loadColoredTexture(sf::Texture& texture, const sf::Color& color,
                        unsigned int width, unsigned int height) {
    sf::Image image;
    image.create(width, height, color);
    return texture.loadFromImage(image);
}

} // namespace

AssetManager& AssetManager::instance() {
    static AssetManager manager;
    return manager;
}

const sf::Texture& AssetManager::getTexture(const std::string& assetName,
                                             const sf::Color& fallbackColor,
                                             unsigned int width,
                                             unsigned int height,
                                             bool* usedFallback) {
    auto it = m_textures.find(assetName);
    if (it != m_textures.end()) {
        if (usedFallback != nullptr) {
            *usedFallback = it->second.usedFallback;
        }
        return it->second.texture;
    }

    TextureEntry entry;
    const bool loaded = entry.texture.loadFromFile(assetName);
    if (!loaded) {
        std::cerr << "Advertencia: textura no encontrada: " << assetName
                  << ". Se usará fallback visual.\n";
        if (!loadColoredTexture(entry.texture, fallbackColor, width, height)) {
            std::cerr << "No se pudo crear fallback para: " << assetName << "\n";
        }
        entry.usedFallback = true;
    } else {
        entry.usedFallback = false;
    }

    if (usedFallback != nullptr) {
        *usedFallback = entry.usedFallback;
    }

    m_textures.emplace(assetName, std::move(entry));
    return m_textures.at(assetName).texture;
}
