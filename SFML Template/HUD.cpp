#include "HUD.hpp"

namespace PixelPanic
{
	HUD::HUD(GameDataRef data) : _data(data)
	{
		this->_scoreText = std::make_unique<sf::Text>(this->_data->assets.GetFont("Flappy Font"));
		this->_scoreText->setString("0");
		this->_scoreText->setCharacterSize(128);
		this->_scoreText->setFillColor(sf::Color::White);
		this->_scoreText->setOrigin({ (float)this->_scoreText->getGlobalBounds().size.x / 2, (float)this->_scoreText->getGlobalBounds().size.y / 2 });
		this->_scoreText->setPosition({ (float)this->_data->window.getSize().x / 2, (float)this->_data->window.getSize().y / 5 });
	}

	HUD::~HUD()
	{
	}

	void HUD::Draw()
	{
		this->_data->window.draw(*this->_scoreText);
	}

	void HUD::UpdateScore(unsigned int score)
	{
		this->_scoreText->setString(std::to_string(score));
	}
}