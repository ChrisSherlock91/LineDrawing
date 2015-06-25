#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Alloc Memeory for size of pixel grid
    pixelGrid.resize(GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        pixelGrid[i].resize(GRID_SIZE);
    }
    
    //Set base position
    auto pos = cocos2d::Vec2(50,1400);
    //loop all number of rows and cols
    for(int k = 0; k < GRID_SIZE; ++k)
    {
        for(int n = 0; n < GRID_SIZE; ++n)
        {
            //create a new slot and set its position
            Slot *currSlot = Slot::create(pos);
            pixelGrid[k][n] = currSlot;
            this->addChild(currSlot);
            pos.x += PIXEL_SIZE;
        }
        pos.y -= PIXEL_SIZE;
        pos.x = 50;
    }
    
    
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
