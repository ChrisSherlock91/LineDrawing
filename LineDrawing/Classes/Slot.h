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
    //Node used for primitive drawing
    cocos2d::DrawNode *node;
    cocos2d::Vec2 position;
    //Polygon verts
    cocos2d::Vec2 rectangle[4];
    //Width/Height pf our pixel
    const int SIZE = 10;
    
public:
    Slot();
    ~Slot();
    void init(cocos2d::Vec2 pos);
    //Draw our square outline
    void Draw();
    //Change the colour to filled
    void ChangeColour();
    //Reset our colour to a border
    bool Contains(double x, double y);
    //Return new slot object
    static Slot* create(cocos2d::Vec2 position);
};


#endif /* defined(__LineDrawing__Tile__) */
