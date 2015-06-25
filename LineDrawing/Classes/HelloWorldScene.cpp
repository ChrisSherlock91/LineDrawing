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
    if ( !Layer::init() )
    {
        return false;
    }
    
    //Set our default line width
    lineWidth = 1;
    
    //General information label
    auto label = Label::createWithTTF("Please Click Two Points on the grid to draw a line!","fonts/Marker Felt.ttf",50);
    label->setPosition(cocos2d::Vec2(1600,1300));
    label->setWidth(400);
    this->addChild(label);
    
    //Add Button with callback to clear function
    auto button = cocos2d::ui::Button::create("PlainBtn.png","PlainBtnDwn.png");
    button->setTitleText("Clear Grid");
    button->setTitleColor(cocos2d::Color3B::BLACK);
    button->setTitleFontSize(40);
    button->cocos2d::Node::setScale(1, 1);
    button->setPosition(Vec2(1600,500));
    button->addTouchEventListener([&](Ref* sender, cocos2d::ui::Widget::TouchEventType type)
    {
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                HelloWorld::ClearGrid();
                break;
            default:
                break;
        }
    });
    this->addChild(button);
    
    auto sizeLbl = Label::createWithTTF("Please Set the width of your line","fonts/Marker Felt.ttf",30);
    sizeLbl->setPosition(cocos2d::Vec2(1650,1050));
    sizeLbl->setWidth(400);
    this->addChild(sizeLbl);
    
    //Create our slider to control our line width
    auto  slider = cocos2d::ui::Slider::create();
    slider->loadBarTexture("Slider_Back.png");
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");
    slider->setScale9Enabled(true);
    slider->setCapInsets(Rect(0, 0, 0, 0));
    slider->setContentSize(Size(250.0f, 19));
    slider->setPosition(cocos2d::Vec2(1650,950));
    slider->addEventListener(CC_CALLBACK_2(HelloWorld::SliderEvent, this));
    this->addChild(slider);
    
    //Label to display our current width
    widthLbl = Label::createWithTTF("Width : " + std::to_string(lineWidth),"fonts/Marker Felt.ttf",30);
    widthLbl->setPosition(cocos2d::Vec2(1650,1000));
    widthLbl->setWidth(400);
    this->addChild(widthLbl);
    
    //Create our grid of pixels
    CreatePixelGrid();

    //Add touch listenr
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    
    //Set touch callback when we begin a touch
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    
    return true;
}

//Used to update our line width called when we move our slider
void HelloWorld::SliderEvent(cocos2d::Ref *pSender, cocos2d::ui::Slider::EventType type)
{
    if (type == cocos2d::ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        //Get slider object
        cocos2d::ui::Slider* slider = dynamic_cast<cocos2d::ui::Slider*>(pSender);
        int percent = slider->getPercent();

        //Dont let it be 0
        if(percent == 0)
        {
            lineWidth = 1;
        }
        else
        {
            //Only want small incrments dont want massive lines
            lineWidth = percent / 10;
        }
        //Update our label with our new width
        widthLbl->setString("Width : " + std::to_string(lineWidth));
    }
}

void HelloWorld::ClearGrid()
{
    //loop grid and reset every colour
    for(int k = 0; k < GRID_SIZE; ++k)
    {
        for(int n = 0; n < GRID_SIZE; ++n)
        {
            pixelGrid[k][n]->Draw();
        }
    }
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    //Check which pixel we collided with
    CheckCollision(touch->getLocation());
    return true;
}

void HelloWorld::CheckCollision(cocos2d::Vec2 pos)
{
    //Loop and check for collision
    for(int k = 0; k < GRID_SIZE; ++k)
    {
        for(int n = 0; n < GRID_SIZE; ++n)
        {
            if(pixelGrid[k][n]->Contains(pos.x, pos.y))
            {
                //Change the colour
                pixelGrid[k][n]->ChangeColour();
                //if its the first point in the line
                if(firstPos.x == 0)
                {
                    //store the position and fill pixel
                    firstPos.x = k;
                    firstPos.y = n;
                    filledPixels.push_back(cocos2d::Vec2(k,n));
                    
                }
                else
                {
                    //its the second point we have picked
                    secondPos.x = k;
                    secondPos.y = n;
                    filledPixels.push_back(cocos2d::Vec2(k,n));
                    //Draw our line between the points
                    DrawLine(firstPos.x,secondPos.x,firstPos.y,secondPos.y,lineWidth);
                    //Now create our output file
                    CreateTextFile();
                }
                break;
            }
        }
    }
}

void HelloWorld::CreateTextFile()
{
    
    auto fs = FileUtils::getInstance();
    auto docDir = fs->getWritablePath();
    //PLEASE CHANGE THIS LINE TO YOUR LOCAL DIRECTORY OR WHEREVER YOU WANT THE FILE TO BE GENERATED
    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    docDir = "/Users/Chris/Documents/Cocos2d-X/LineDrawRepo/LineDrawing/";
    //*********************************************************************************************
    //*********************************************************************************************
    //*********************************************************************************************
    auto filePath = docDir + "OUTPUT.txt";
    //Remove old file
    fs->removeFile(filePath);
    //open our new file
    std::ofstream myfile;
    myfile.open (filePath);
    //Write into the stream our information
    myfile << "Grid Dimension : 128" << std::endl;
    myfile << "Path Width : " << std::to_string(lineWidth) << std::endl;
    myfile << "Start Point : " << std::to_string((int)(filledPixels.at(0).x)) << "," << std::to_string((int)(filledPixels.at(0).y)) << std::endl;
    myfile << "End Point : " << std::to_string((int)(filledPixels.at(1).x)) << "," << std::to_string((int)(filledPixels.at(1).y)) << std::endl;
    myfile << "All Other Points Filled : " << std::endl;
    
    //Loop all stored pixels and write them to the file
    for(int i = 2; i < filledPixels.size(); ++i)
    {
        myfile << std::to_string((int)(filledPixels.at(i).x)) << "," << std::to_string((int)(filledPixels.at(i).y)) << std::endl;
    }
    myfile.close();
    
    //Empty stored points so we can start for new line
    filledPixels.clear();
    
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
            filledPixels.push_back(cocos2d::Vec2(x0,y2));
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
            filledPixels.push_back(cocos2d::Vec2(x2+sx,y0));
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
