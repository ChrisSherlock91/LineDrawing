//
//  Tile.h
//  LineDrawing
//
//  Created by Chris Sherlock on 25/06/2015.
//
//

#ifndef __LineDrawing__Tile__
#define __LineDrawing__Tile__

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"

class Slot : public cocos2d::Layer
{
protected:
    cocos2d::DrawNode *node;
    cocos2d::Vec2 position;
    cocos2d::Vec2 rectangle[4];
    const int WIDTH = 10;
    
public:
    
    Slot();
    ~Slot();
    void init(cocos2d::Vec2 pos);
    void update(float dt);
    void Draw();
    void ChangeColour();
    void ResetColour();
    bool Contains(double x, double y);
    cocos2d::Vec2 GetPosition();
    static Slot* create(cocos2d::Vec2 position);
};


#endif /* defined(__LineDrawing__Tile__) */
