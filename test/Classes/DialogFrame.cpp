#include "DialogFrame.h"

USING_NS_CC;

DialogFrame* DialogFrame::create(const std::string& content)
{
    DialogFrame* dialogFrame = new (std::nothrow) DialogFrame();
    if (dialogFrame && dialogFrame->init(content))
    {
        dialogFrame->ifCreated = true;
        dialogFrame->autorelease();
        return dialogFrame;
    }
    CC_SAFE_DELETE(dialogFrame);
    return nullptr;
}

bool DialogFrame::init(const std::string& content)
{
    if (!Layer::init())
    {
        return false;
    }

    // 初始化UI
    initUI(content);

    // 初始化对话索引
    currentDialogIndex = 0;

    return true;
}

void DialogFrame::initUI(const std::string& content)
{
    // 创建对话框背景
    background = Sprite::create("DialogFrame/textBox.png");
    background->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 10));
    this->addChild(background);

    // 创建对话内容标签
    contentLabel = Label::createWithTTF(content, "fonts/arial.ttf", 24);
    contentLabel->setColor(Color3B::BLACK);
    contentLabel->setPosition(background->getContentSize().width / 2, background->getContentSize().height / 2);
    background->addChild(contentLabel);

    //// 创建关闭按钮
    //auto closeButton = MenuItemImage::create("DialogFrame/cancelBotton.png", "DialogFrame/cancelBotton.png", [this](Ref* sender) {
    //    if (closeCallback)
    //    {
    //        closeCallback();
    //    }
    //    this->closeDialog();
    //    });
    //closeButton->setPosition(background->getContentSize().width - closeButton->getContentSize().width / 2, background->getContentSize().height - closeButton->getContentSize().height / 2);

    //// 创建下一个对话按钮
    //auto nextButton = MenuItemImage::create("DialogFrame/nextBotton.png", "DialogFrame/nextBotton.png", [this](Ref* sender) {
    //    this->nextDialog();
    //    });
    //nextButton->setPosition(background->getContentSize().width / 2, nextButton->getContentSize().height / 2);

    auto menu = Menu::create(nullptr);
    menu->setPosition(Vec2::ZERO);
    background->addChild(menu);

    // 创建头像
    avatarSprite = Sprite::create("characters/portraits/Abigail/Abigail_common.png");
    if (avatarSprite)
    {
        avatarSprite->setPosition(Vec2(avatarSprite->getContentSize().width / 2 + 100, background->getContentSize().height - avatarSprite->getContentSize().height / 2 + 50));
        avatarSprite->setScale(2);
        background->addChild(avatarSprite);
    }
}

void DialogFrame::updateContent(const std::string& newContent)
{
    contentLabel->setString(newContent);
}

void DialogFrame::closeDialog()
{
    ifCreated = false;
    this->_parent->removeChild(this);
}

void DialogFrame::setCloseCallback(const std::function<void()>& callback)
{
    closeCallback = callback;
}

void DialogFrame::setAvatar(const std::string& avatarPath)
{
    if (avatarSprite)
    {
        avatarSprite->setTexture(avatarPath);
    }
}

void DialogFrame::setDialogList(const std::vector<std::string>& dialogList)
{
    this->dialogList = dialogList;
    currentDialogIndex = 0;
    if (!dialogList.empty())
    {
        updateContent(dialogList[currentDialogIndex]);
    }
}

void DialogFrame::nextDialog()
{
    currentDialogIndex++;
    if (currentDialogIndex < dialogList.size())
    {
        updateContent(dialogList[currentDialogIndex]);
    }
}