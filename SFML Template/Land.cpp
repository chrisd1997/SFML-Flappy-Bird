#include "Land.hpp"
#include "DEFINITIONS.hpp"

namespace PixelPanic
{
	Land::Land(GameDataRef data) : _data(data)
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Land"));
		sf::Sprite sprite2(this->_data->assets.GetTexture("Land"));

		sprite.setPosition({ 0.0f, (float)this->_data->window.getSize().y - (float)sprite.getGlobalBounds().size.y });
		sprite2.setPosition({ (float)sprite.getGlobalBounds().size.x , (float)this->_data->window.getSize().y - (float)sprite.getGlobalBounds().size.y });

		this->_landSprites.push_back(sprite);
		this->_landSprites.push_back(sprite2);
	}

	void Land::MoveLand(float dt)
	{
		for (unsigned short int i = 0; i < this->_landSprites.size(); i++)
		{
			float movement = PIPE_MOVEMENT_SPEED * dt;

			this->_landSprites.at(i).move({ -movement, 0.0f });

			if (this->_landSprites.at(i).getPosition().x < 0 - this->_landSprites.at(i).getGlobalBounds().size.x)
			{
				sf::Vector2f position({ (float)this->_data->window.getSize().x, (float)this->_landSprites.at(i).getPosition().y });

				this->_landSprites.at(i).setPosition(position);
			}
		}
	}

	void Land::DrawLand()
	{
		for (unsigned short int i = 0; i < this->_landSprites.size(); i++)
		{
			this->_data->window.draw(this->_landSprites.at(i));
		}
	}

	const std::vector<sf::Sprite>& Land::GetSprites() const
	{
		return this->_landSprites;
	}
}