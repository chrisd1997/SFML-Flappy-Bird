#include "Pipe.hpp"

namespace PixelPanic
{
	Pipe::Pipe(GameDataRef data) : _data(data)
	{
		this->_landHeight = this->_data->assets.GetTexture("Land").getSize().y;
		this->_pipeSpawnYOffset = 0;
	}

	void Pipe::SpawnBottomPipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Up"));

		sprite.setPosition({ (float)this->_data->window.getSize().x, (float)this->_data->window.getSize().y - sprite.getGlobalBounds().size.y - this->_pipeSpawnYOffset });

		this->_pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnTopPipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Down"));

		sprite.setPosition({ (float)this->_data->window.getSize().x, (float)-this->_pipeSpawnYOffset });

		this->_pipeSprites.push_back(sprite);
	}

	void Pipe::SpawnInvisiblePipe()
	{
		sf::Sprite sprite(this->_data->assets.GetTexture("Pipe Up"));

		sprite.setPosition({ (float)this->_data->window.getSize().x, (float)this->_data->window.getSize().y - sprite.getGlobalBounds().size.y });
		sprite.setColor(sf::Color(0, 0, 0, 0));

		this->_pipeSprites.push_back(sprite);
	}

	void Pipe::MovePipes(float dt)
	{
		for (unsigned short int i = 0; i < this->_pipeSprites.size(); i++)
		{
			if (this->_pipeSprites.at(i).getPosition().x < 0 - this->_pipeSprites.at(i).getGlobalBounds().size.x)
			{
				this->_pipeSprites.erase(this->_pipeSprites.begin() + i);
			}
			else
			{
				float movement = PIPE_MOVEMENT_SPEED * dt;

				this->_pipeSprites.at(i).move({ -movement, 0 });
			}
		}
	}

	void Pipe::DrawPipes()
	{
		for (unsigned short int i = 0; i < this->_pipeSprites.size(); i++)
		{
			this->_data->window.draw(this->_pipeSprites.at(i));
		}
	}

	void Pipe::RandomizePipeOffset()
	{
		this->_pipeSpawnYOffset = rand() % (_landHeight + 1);
	}

	const std::vector<sf::Sprite>& Pipe::GetSprites() const
	{
		return this->_pipeSprites;
	}
}