//
//  Tile.cpp
//  LineDrawing
//
//  Created by Chris Sherlock on 25/06/2015.
//
//

#include "Slot.h"

Slot::Slot(){}

Slot::~Slot(){}

void Slot::init(cocos2d::Vec2 pos)
{
    position = pos;
    node = cocos2d::DrawNode::create();
    this->addChild(node);
    //Draw our Square
    rectangle[0] = cocos2d::Vec2(pos.x,pos.y);
    rectangle[1] = cocos2d::Vec2(pos.x + SIZE, pos.y);
    rectangle[2] = cocos2d::Vec2(pos.x + SIZE, pos.y + SIZE);
    rectangle[3] = cocos2d::Vec2(pos.x, pos.y + SIZE);
    Draw();
}

//Fill in our square
void Slot::ChangeColour()
{
    cocos2d::Color4F white(1, 1, 1, 1);
    cocos2d::Color4F alpha(1, 1, 1, 1);
    node->drawPolygon(rectangle, 4, alpha, 0.5, white);
}

//Draw our outline
void Slot::Draw()
{
    node->clear();
    cocos2d::Color4F white(249, 32, 32, 1);
    cocos2d::Color4F alpha(249, 32, 32, 0);
    node->drawPolygon(rectangle, 4, alpha, 0.5, white);
}

bool Slot::Contains(double x, double y)
{
    //Check if point is inside our square
    if (x < (position.x + (.5 * SIZE)) && x > (position.x - (.5 * SIZE)) &&
        y < (position.y + (.5 * SIZE)) && y > (position.y) - (.5 *SIZE))
        return true;
    else
        return false;
}

//Create and return slot object
Slot* Slot::create(cocos2d::Vec2 position)
{
    Slot* pSprite = new Slot();
    if (pSprite)
    {
        pSprite->autorelease();
        pSprite->init(position);
        return pSprite;
    }
    
    CC_SAFE_DELETE(pSprite);
    return NULL;
}