#include "Flash.hpp"

namespace PixelPanic
{
	Flash::Flash(GameDataRef data) : _data(data)
	{
		this->_shape = sf::RectangleShape(sf::Vector2f(this->_data->window.getSize()));
		this->_shape.setFillColor(sf::Color(255, 255, 255, 0));

		this->_flashOn = true;
	}

	void Flash::Show(float dt)
	{
		if (this->_flashOn)
		{
			int alpha = (int)this->_shape.getFillColor().a + (FLASH_SPEED * dt);

			if (alpha >= 255.0f)
			{
				alpha = 255.0f;

				this->_flashOn = false;
			}

			this->_shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
		else
		{
			int alpha = (int)this->_shape.getFillColor().a - (FLASH_SPEED * dt);

			if (alpha < 0.0f)
			{
				alpha = 0.0f;

				this->_flashOn = false;
			}

			this->_shape.setFillColor(sf::Color(255, 255, 255, alpha));
		}
	}

	void Flash::Draw()
	{
		this->_data->window.draw(this->_shape);
	}
}