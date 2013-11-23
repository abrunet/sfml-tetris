#ifndef RESOURCE_MANAGER_HPP__
#define RESOURCE_MANAGER_HPP__

#include "TetrominoShape.hpp"

#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/Color.hpp>

#include <vector>

class ResourceManager {

public:
    static ResourceManager& getInstance() {
        static ResourceManager instance;
        return instance;
    }

    const sf::Image& getTetrominoImage() const;
    const sf::Color& getColor(TetrominoShape::Shape shape) const;

private:
    ResourceManager();
    ResourceManager(ResourceManager const&);
    void operator=(ResourceManager const&);

    sf::Image cubeImage;
    std::vector<sf::Color> colors;
};

#endif // RESOURCE_MANAGER_HPP__

