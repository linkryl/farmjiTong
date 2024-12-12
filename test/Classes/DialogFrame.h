#pragma once
#include "cocos2d.h"

class DialogFrame : public cocos2d::Layer
{
public:
    // ����һ���Ի���ʵ��
    static DialogFrame* create(const std::string& content);

    // ��ʼ���Ի���
    virtual bool init(const std::string& content);

    // ���¶Ի�����
    void updateContent(const std::string& newContent);

    // �رնԻ���
    void closeDialog();

    // ���ùرհ�ť�Ļص�����
    void setCloseCallback(const std::function<void()>& callback);

private:
    // ��ʼ��UIԪ��
    void initUI(const std::string& content);

    // �رհ�ť�Ļص�����
    std::function<void()> closeCallback;

    // �Ի��򱳾�
    cocos2d::Sprite* background;

    // �Ի����ݱ�ǩ
    cocos2d::Label* contentLabel;
};