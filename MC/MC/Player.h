#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "ItemStack.h"

class Player {
public:
    Player();
//    void handleInput(const sf::Window& window, Keyboard& keyboard);
//    void update(float dt, World& wolrd);
//    void collide(World& world, const glm::vec3& vel, float dt);
    void addItem(int itemindex);
 //   void draw(RenderMaster& master);
    ItemStack& getHeldItems();

private:
    void jump();
//    void keyboardInput(Keyboard& keyboard);
 //   void mouseInput(const sf::Window& window);
    bool m_isOnGround = false;
    bool m_isFlying = false;//judge flying state
    ItemStack MyBag;

 //   std::vector<sf::Text> m_itemText;
 //   sf::Text m_posPrint;
 //   int m_heldItem = 0;
 /*   ToggleKey m_itemDown;
    ToggleKey m_itemUp;
    ToggleKey m_flyKey;

    ToggleKey m_num1;
    ToggleKey m_num2;
    ToggleKey m_num3;
    ToggleKey m_num4;
    ToggleKey m_num5;

    glm::vec3 m_acceleration;
    */
};


#endif