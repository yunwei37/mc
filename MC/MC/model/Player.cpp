#include "Player.h"
#include <iostream>
#include <sstream>



/*Player::Player()
	: Entity({ 2500, 125, 2500 }, { 0.f, 0.f, 0.f }, { 0.3f, 1.f, 0.3f })
	, m_itemDown(sf::Keyboard::Down)
	, m_itemUp(sf::Keyboard::Up)
	, m_flyKey(sf::Keyboard::F)
	, m_num1(sf::Keyboard::Num1)
	, m_num2(sf::Keyboard::Num2)
	, m_num3(sf::Keyboard::Num3)
	, m_num4(sf::Keyboard::Num4)
	, m_num5(sf::Keyboard::Num5)
	, m_acceleration(glm::vec3(0.f))

{
	f.loadFromFile("Res/Fonts/rs.ttf");

	for (int i = 0; i < 5; i++) {
		m_items.emplace_back(Material::NOTHING, 0);
	}

	for (float i = 0; i < 5; i++) {
		sf::Text t;
		t.setFont(f);
		t.setOutlineColor(sf::Color::Black);
		t.setCharacterSize(25);
		t.setPosition({ 20.0f, 20.0f * i + 100.0f });
		m_itemText.push_back(t);
	}
	m_posPrint.setFont(f);
	m_posPrint.setOutlineColor(sf::Color::Black);
	m_posPrint.setCharacterSize(25);
	m_posPrint.setPosition(20.0f, 20.0f * 6.0f + 100.0f);
}*/

void Player::addItem(int itemindex)
{
	MyBag.add(itemindex, 1);
}


Player::Player()
{
	inHand = Block::Stone;//defalut
}
