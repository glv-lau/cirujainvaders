#pragma once
#include <SFML/Graphics.hpp>
#include <map>
#include <iostream>
#include <string>
#include <unordered_map>

class TextureManager {
public:
    struct TextureEntry {
        sf::Texture texture;
        bool loaded = false;
    };
    static TextureManager& getInstance(){
        static TextureManager instance;
        return instance;
    }
    const sf::texture& gettexture(const std::string& id,const sf::Color& fallbackColor, unsigned int width, unsigned int height, bool* usedFallback = nullptr) {
        auto it = textures.find(id);
        if (it != textures.end()) {
            if (usedFallback != nullptr) {
                *usedFallback = it->second.usedFallback;
            }
            return it->second.texture;
        }
        TextureEntry Entry;
    const bool loaded = entry.texture.loadFromFile(filename);
    if (!loaded) {
        std::cerr << "Failed to load texture: " << filename << std::endl;
        sf:: Image image;
        image.create(width, height, fallbackColor);
        if(!entry.texture.loadFromImage(image)) {
            std::cerr << "Failed to create fallback texture for: " << filename << std::endl;
        }
        Entry.usedFallback = true;
    } else {
        entry.usedFallback = false;
    }
    if (usedFallback != nullptr) {
        *usedFallback = entry.usedFallback;
    }
    m_textures.emplace(id, std::move(entry));
    return m_textures.at(id).texture;
    }
    

private:
    TextureManager();
    std::unordered_map<std::string, sf::Texture> textures;
};