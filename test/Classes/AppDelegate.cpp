#include <thread>

#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "Scenes/FarmScene.h"
#include "Scenes/TownScene.h"
#include "Scenes/WoodsScene.h"
#include "Scenes/CaveScene.h"
#include "Scenes/MountainScene.h"
#include "Scenes/FarmHouseScene.h"
#include "Systems/Farm_system.h"
#include "Systems/Livestock_farm_system.h"
#include "Time_system.h"
#include "Constant.h"
#include "PlayerData.h"
#include "CommercialSystem.h"
#include "InitialScene.h"
#include "StartupScene.h"

Farm_system farm_system(FARM_OFFSET_X * 16, FARM_OFFSET_Y * 16);
Liverstock_farm_system live_farm_system(LIVE_FARM_OFFSET_X * 16, LIVE_FARM_OFFSET_Y * 16);
Time_system time_system;
// 默认在家门口出生
PlayerInfo playerInfo{ HOME_X, HOME_Y, DOWN };

// 物品映射遵照如下编码： 
// 
// 1110为蔬菜作物，1100为蔬菜种子，1120为收获的蔬菜 
// 1111为谷物作物，1101为谷物种子，1121为收获的谷物 
// 2110为猪，2100为猪仔，2120为猪肉 

// 作物id映射到物品名
std::map<int, std::string> crop_names{ {1110, "parsnip"}, { 1111, "wheat" }, {2110, "pig"} };
// 作物id映射到作物素材图片数量
std::map<int, int> crop_image_number{ {1110, 6}, { 1111, 6 }, {2110, 2} };

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

//static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
//static cocos2d::Size designResolutionSize = cocos2d::Size(16 * 80, 16 * 65);
static cocos2d::Size designResolutionSize = cocos2d::Size(1600, 900);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

// if you want a different context, modify the value of glContextAttrs
// it will affect all platforms
void AppDelegate::initGLContextAttrs()
{
    // set OpenGL context attributes: red,green,blue,alpha,depth,stencil,multisamplesCount
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// if you want to use the package manager to install more packages,  
// don't modify or remove this function
static int register_all_packages()
{
    return 0; //flag for packages manager
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("testCpp2", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
        glview = GLViewImpl::create("testCpp2");
#endif
        director->setOpenGLView(glview);
    }

    // turn on display FPS
    //director->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0f / 60);
#if 0
    // Set the design resolution
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::NO_BORDER);
    auto frameSize = glview->getFrameSize();
    // if the frame's height is larger than the height of medium size.
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is larger than the height of small size.
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // if the frame's height is smaller than the height of medium size.
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
#endif

    register_all_packages();

    // 获取 Director 的 _notificationNode
    auto notificationNode = Director::getInstance()->getNotificationNode();
    // 如果 _notificationNode 为空，则创建一个新的 Node
    if (!notificationNode) {
        notificationNode = Node::create();
        Director::getInstance()->setNotificationNode(notificationNode);
    }

    // create a scene. it's an autorelease object
    //auto scene = HelloWorld::createScene();
    srand(time(0));

    auto commercialSysterm = CommercialSystem::getInstance();
    // 商品价格
    const std::vector<pair<int, int>> prices =
    {
        {1100,10},{1101,8}, {1102,5},
        {2100,300}, {3020,5}, {3021,6},
        {3022,30}, {3023,15}, {3024,100},
        {3025,500}, {3026,2000}, {3027,10000},
        {3101,50},{3120,3},{3121,20},
        {3122,500},{3122,500},{3124,800},
        {3125,850},{3126,15000}
    };
    commercialSysterm->initialize_price(prices);
    //FarmScene
    auto scene = StartupScene::createScene();
    // run
    director->runWithScene(scene);


    return true;
}

// This function will be called when the app is inactive. Note, when receiving a phone call it is invoked.
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
