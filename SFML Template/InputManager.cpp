#include "InputManager.hpp"

namespace PixelPanic
{
	bool InputManager::IsSpriteClicked(sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window)
	{
		if (sf::Mouse::isButtonPressed(button))
		{
			// Draw a temporary rect to determine the hitbox
			sf::IntRect tempRect({ (int)object.getPosition().x, (int)object.getPosition().y }, { (int)object.getGlobalBounds().size.x, (int)object.getGlobalBounds().size.y });

			// If the mouse button is inside of the rect
			if (tempRect.contains(sf::Mouse::getPosition(window)))
			{
				return true;
			}
		}

		return false;
	}

	sf::Vector2i InputManager::GetMousePosition(sf::RenderWindow& window)
	{
		return sf::Mouse::getPosition(window);
	}
}