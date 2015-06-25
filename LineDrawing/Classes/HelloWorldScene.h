#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Slot.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include <fstream>

class HelloWorld : public cocos2d::Layer
{
protected:
    //Size of pixel grid
    const int GRID_SIZE = 128;
    //Width/height of each pixel
    const int PIXEL_SIZE = 10;
    //Width of the line
    int lineWidth;
    //2d vector to store our grid
    std::vector<std::vector<Slot*>> pixelGrid;
    //used to store filled pixels for our output document
    std::vector<cocos2d::Vec2> filledPixels;
    
    //Positions for the two touches
    cocos2d::Vec2 firstPos;
    cocos2d::Vec2 secondPos;
    
    //Changable label for our width slider
    cocos2d::Label *widthLbl;
    
public:
    
    //Will create and draw our grid of pixels
    void CreatePixelGrid();
    //Touch callback for when we press inside our grid
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event * event);
    //Check which pixel you have collided with
    void CheckCollision(cocos2d::Vec2 pos);
    //Draw our line between our two points and the width
    void DrawLine(double x0,double x1, double y0, double y1, int wd);
    //Creates our output file
    void CreateTextFile();
    //Clears the grid of drawn lines
    void ClearGrid();
    //Callback for movement on our slider
    void SliderEvent(Ref *pSender, cocos2d::ui::Slider::EventType type);
    
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
