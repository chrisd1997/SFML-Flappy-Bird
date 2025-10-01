#include "Bird.hpp"

namespace PixelPanic
{
	Bird::Bird(GameDataRef data) : _data(data)
	{
		this->_animationIterator = 0;

		this->_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 1"));
		this->_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 2"));
		this->_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 3"));
		this->_animationFrames.push_back(this->_data->assets.GetTexture("Bird Frame 4"));

		this->_birdSprite = std::make_unique<sf::Sprite>(this->_animationFrames.at(this->_animationIterator));

		this->_birdSprite->setPosition({ (this->_data->window.getSize().x / 4) - (this->_birdSprite->getGlobalBounds().size.x / 2), (this->_data->window.getSize().y / 2) - (this->_birdSprite->getGlobalBounds().size.y / 2) });

		this->_birdState = BIRD_STATE_STILL;

		sf::Vector2f origin = sf::Vector2f({ (float)this->_birdSprite->getGlobalBounds().size.x / 2, (float)this->_birdSprite->getGlobalBounds().size.y / 2 });
		this->_birdSprite->setOrigin(origin);

		this->_rotation = 0;
	}

	void Bird::Draw()
	{
		this->_data->window.draw(*this->_birdSprite);
	}

	void Bird::Animate(float dt)
	{
		if (_clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / this->_animationFrames.size())
		{
			if (this->_animationIterator < this->_animationFrames.size() - 1)
			{
				this->_animationIterator++;
			}
			else
			{
				this->_animationIterator = 0;
			}

			this->_birdSprite->setTexture(this->_animationFrames.at(this->_animationIterator));

			this->_clock.restart();
		}
	}

	void Bird::Update(float dt)
	{
		if (BIRD_STATE_FALLING == this->_birdState)
		{
			this->_birdSprite->move({ 0.0f, GRAVITY * dt });

			this->_rotation += ROTATION_SPEED * dt;

			if (this->_rotation > 25.0f)
			{
				this->_rotation = 25.0f;
			}

			this->_birdSprite->setRotation(sf::degrees(this->_rotation));
		}
		else if (BIRD_STATE_FLYING == this->_birdState)
		{
			this->_birdSprite->move({ 0.0f, -FLYING_SPEED * dt });

			this->_rotation -= ROTATION_SPEED * dt;

			if (this->_rotation < -25.0f)
			{
				this->_rotation = -25.0f;
			}

			this->_birdSprite->setRotation(sf::degrees(this->_rotation));
		}

		if (this->_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION)
		{
			this->_movementClock.restart();

			this->_birdState = BIRD_STATE_FALLING;
		}
	}

	void Bird::Tap()
	{
		this->_movementClock.restart();
		this->_birdState = BIRD_STATE_FLYING;
	}
}