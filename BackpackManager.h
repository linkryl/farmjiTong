#include "cocos2d.h"
#include "BackpackLayer.h"

//���� BackpackManager ������, �������������������ں��߼�
class BackpackManager
{
public:
    // ��ȡ����ʵ��
    static BackpackManager* getInstance();

    // ��ʾ������
    bool showBackpack(Node* parent);

    // ���ر�����
    void hideBackpack();

    // �����Ʒ������
    bool addItem(const std::string& itemImagePath);

    // ��鱳���Ƿ�����
    bool isFull() const;
private:
    BackpackManager();  // ���캯��˽�л�
    ~BackpackManager(); // ��������

    Layer* backpackLayer; // ������
    int maxItems;                  // ������Ʒ����
    int currentItems;              // ��ǰ�����е���Ʒ����
};
