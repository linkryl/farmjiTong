#include "DialogFrame.h"

USING_NS_CC;

DialogFrame* DialogFrame::create(const std::string& content)
{
    DialogFrame* dialogFrame = new (std::nothrow) DialogFrame();
    if (dialogFrame && dialogFrame->init(content))
    {
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

    return true;
}

void DialogFrame::initUI(const std::string& content)
{
    // 创建对话框背景
    background = Sprite::create("DialogFrame/textBox.png");
    background->setPosition(Vec2(Director::getInstance()->getWinSize().width / 2, Director::getInstance()->getWinSize().height / 2));
    this->addChild(background);

    // 创建对话内容标签
    contentLabel = Label::createWithTTF(content, "fonts/arial.ttf", 24);
    contentLabel->setColor(Color3B::BLACK);
    contentLabel->setPosition(background->getContentSize().width / 2, background->getContentSize().height / 2);
    background->addChild(contentLabel);

    // 创建关闭按钮
    auto closeButton = MenuItemImage::create("DialogFrame/cancelBotton.png", "DialogFrame/cancelBotton.png", [this](Ref* sender) {
        if (closeCallback)
        {
            closeCallback();
        }
        this->closeDialog();
        });
    closeButton->setPosition(background->getContentSize().width - closeButton->getContentSize().width / 2, background->getContentSize().height - closeButton->getContentSize().height / 2);

    auto menu = Menu::create(closeButton, nullptr);
    menu->setPosition(Vec2::ZERO);
    background->addChild(menu);
}

void DialogFrame::updateContent(const std::string& newContent)
{
    contentLabel->setString(newContent);
}

void DialogFrame::closeDialog()
{
    this->removeFromParentAndCleanup(true);
}

void DialogFrame::setCloseCallback(const std::function<void()>& callback)
{
    closeCallback = callback;
}