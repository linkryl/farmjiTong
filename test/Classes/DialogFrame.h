#pragma once
#include "cocos2d.h"

class DialogFrame : public cocos2d::Layer
{
public:
    // 创建一个对话框实例
    static DialogFrame* create(const std::string& content);

    // 初始化对话框
    virtual bool init(const std::string& content);

    // 更新对话内容
    void updateContent(const std::string& newContent);

    // 关闭对话框
    void closeDialog();

    // 设置关闭按钮的回调函数
    void setCloseCallback(const std::function<void()>& callback);

    // 设置头像图片
    void setAvatar(const std::string& avatarPath);

    // 设置对话列表
    void setDialogList(const std::vector<std::string>& dialogList);

    // 切换到下一句对话
    void nextDialog();

private:
    // 初始化UI元素
    void initUI(const std::string& content);

    // 关闭按钮的回调函数
    std::function<void()> closeCallback;

    // 对话框背景
    cocos2d::Sprite* background;

    // 对话内容标签
    cocos2d::Label* contentLabel;

    // 头像
    cocos2d::Sprite* avatarSprite;

    // 对话列表
    std::vector<std::string> dialogList;

    // 当前对话的索引
    int currentDialogIndex;
};