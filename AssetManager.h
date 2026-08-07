#pragma once

#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
#include <string>
#include <unordered_map>

class AssetManager {
public:
    struct TextureEntry {
        sf::Texture texture;
        bool usedFallback = false;
    };

    static AssetManager& instance() {
        static AssetManager manager;
        return manager;
    }

    const sf::Texture& getTexture(const std::string& assetName,
                                  const sf::Color& fallbackColor,
                                  unsigned int width,
                                  unsigned int height,
                                  bool* usedFallback = nullptr) {
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
            sf::Image image;
            image.create(width, height, fallbackColor);
            if (!entry.texture.loadFromImage(image)) {
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

private:
    AssetManager() = default;

    std::unordered_map<std::string, TextureEntry> m_textures;
};
