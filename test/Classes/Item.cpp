#include "Item.h"

Bag* Bag::_instance = nullptr;

Bag* Bag::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = new (std::nothrow) Bag();
    }
    return _instance;
}

Bag::Bag()
{
    addItem(4001, 1000);
    if (!_items.empty())
    {
        auto it = _items.begin();
        itemInHand = it->first;
    }
}

Bag::~Bag()
{
    _items.clear();
}

void Bag::addItem(int itemId, int quantity)
{
    auto it = _items.find(itemId);
    if (it != _items.end())
    {
        it->second += quantity;
    }
    else
    {
        _items[itemId] = quantity;
    }
}

bool Bag::removeItem(int itemId, int quantity)
{
    auto it = _items.find(itemId);
    if (it != _items.end())
    {
        if (it->second >= quantity)
        {
            it->second -= quantity;
            if (it->second <= 0)
            {
                _items.erase(it);
            }
            return true;
        }
    }
    return false;
}

int Bag::getItemQuantity(int itemId) const
{
    auto it = _items.find(itemId);
    if (it != _items.end())
    {
        return it->second;
    }
    return 0;
}