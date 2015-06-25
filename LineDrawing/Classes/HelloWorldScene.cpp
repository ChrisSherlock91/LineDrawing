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
    
    CreatePixelGrid();

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    //listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    //listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    CCLOG("onTouchBegan x = %f, y = %f", touch->getLocation().x, touch->getLocation().y);
    
    CheckCollision(touch->getLocation());
    
    return true;
}

void HelloWorld::CheckCollision(cocos2d::Vec2 pos)
{

    for(int k = 0; k < GRID_SIZE; ++k)
    {
        for(int n = 0; n < GRID_SIZE; ++n)
        {
            if(pixelGrid[k][n]->Contains(pos.x, pos.y))
            {
                pixelGrid[k][n]->ChangeColour();
                if(firstPos.x == 0)
                {
                    firstPos.x = k;
                    firstPos.y = n;
                }
                else
                {
                    secondPos.x = k;
                    secondPos.y = n;
                    DrawLine(firstPos.x,secondPos.x,firstPos.y,secondPos.y,4);
                }
                break;
            }
        }
    }
}

void HelloWorld::DrawLine(double x0,double x1, double y0, double y1, int width)
{
    firstPos = cocos2d::Vec2(0,0);
    secondPos = cocos2d::Vec2(0,0);
    
    //Delta X direction
    int dx = std::abs(x1-x0);
    //Slope of X
    int sx = x0 < x1 ? 1 : -1;
    //Delta Y direction
    int dy = std::abs(y1-y0);
    //Slop of Y
    int sy = y0 < y1 ? 1 : -1;
    //Error amount
    int err = dx-dy;
    //Error value and new end pos
    int e2, x2, y2;
    
    float ed = dx+dy == 0 ? 1 : sqrt((float)dx * dx +(float)dy * dy);
    
    for (width = (width + 1) / 2; ;)
    {
        //Set Colour of new pixel
        pixelGrid[x0][y0]->ChangeColour();
        //Set Error
        e2 = err;
        //Reset new end pos
        x2 = x0;
        //Step in X direction
        if (2 * e2 >= -dx)
        {
            //Loop error to get all tiles off from centre line
            for (e2 += dy, y2 = y0; e2 < ed * width && (y1 != y2 || dx > dy); e2 += dx)
            //Change current Pixel
            pixelGrid[x0][y2]->ChangeColour();
            //If same tile
            if (x0 == x1) break;
            //Calc new err
            e2 = err;
            err -= dy;
            x0 += sx;
        }
        if (2 * e2 <= dy)
        {
            //Loop error to get all tiles off from centre line
            for (e2 = dx-e2; e2 < ed*width && (x1 != x2 || dx < dy); e2 += dy)
            //Change current Pixel
            pixelGrid[x2+=sx][y0]->ChangeColour();
            //If same tile
            if (y0 == y1) break;
            //Calc new error
            err += dx;
            y0 += sy;
        }
    }
}


void HelloWorld::CreatePixelGrid()
{
    //Alloc Memeory for size of pixel grid
    pixelGrid.resize(GRID_SIZE);
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        pixelGrid[i].resize(GRID_SIZE);
    }

    int posX = 5;
    //Set base position
    auto pos = cocos2d::Vec2(posX,1450);
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
        pos.x = posX;
    }

}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
