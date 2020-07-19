#pragma once
#ifndef PLAYER_H
#define PLAYER_H
#include "Camera.h"
#include "Block.h"
#include <vector>
#include "ItemStack.h"

class Player {
public:
    Player(Camera *myCamera);
	void getPlacingPos(int worldPos[]);//get placing world position
	
//    void handleInput(const sf::Window& window, Keyboard& keyboard);
//    void update(float dt, World& wolrd);
//    void collide(World& world, const glm::vec3& vel, float dt);
    void addItem(int itemindex);
 //   void draw(RenderMaster& master);
    //ItemStack& getHeldItems();

	Camera *myCamera;
	Block::blockType inHand;//block type in hand
//    void jump();
//    void keyboardInput(Keyboard& keyboard);
 //   void mouseInput(const sf::Window& window);
    bool m_isOnGround = false;
    bool m_isFlying = false;//judge flying state
    ItemStack MyBag;

 //   std::vector<sf::Text> m_itemText;
 //   sf::Text m_posPrint;
 //   int m_heldItem = 0;

};


#endif