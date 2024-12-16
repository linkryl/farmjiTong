#include "cocos2d.h"
#include "BackpackLayer.h"

//创建 BackpackManager 单例类, 负责管理背包层的生命周期和逻辑
class BackpackManager
{
public:
    // 获取单例实例
    static BackpackManager* getInstance();

    // 显示背包层
    bool showBackpack(Node* parent);

    // 隐藏背包层
    void hideBackpack();

    // 添加物品到背包
    bool addItem(const std::string& itemImagePath);

    // 检查背包是否已满
    bool isFull() const;
private:
    BackpackManager();  // 构造函数私有化
    ~BackpackManager(); // 析构函数

    Layer* backpackLayer; // 背包层
    int maxItems;                  // 背包物品上限
    int currentItems;              // 当前背包中的物品数量
};
