#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Slot.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include <fstream>

class HelloWorld : public cocos2d::Layer
{
public:
    const int GRID_SIZE = 128;
    const int PIXEL_SIZE = 10;
    std::vector<std::vector<Slot*>> pixelGrid;
    std::vector<cocos2d::Vec2> filledPixels;
    
    cocos2d::Vec2 firstPos;
    cocos2d::Vec2 secondPos;
    
    void CreatePixelGrid();
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    void CheckCollision(cocos2d::Vec2 pos);
    
    void DrawLine(double x0,double x1, double y0, double y1, int wd);
    
    bool Contains(double x, double y);
    
    void CreateTextFile();
    
    void ClearGrid();
    
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
