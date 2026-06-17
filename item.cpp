#include "Item.h"
#include <iostream>

using namespace std;

Item::Item(string n, string t, int ev, int c, int q) : name(n), type(t), effectValue(ev), cost(c), quantity(q) {}

string Item::getName()
{
    return name;
}
string Item::getType()
{
    return type;
}
int Item::getEffectValue()
{
    return effectValue;
}
int Item::getQuantity()
{
    return quantity;
}
int Item::getCost()
{
    return cost;
}

void Item::addQuantity(int q)
{
    quantity += q;
}
void Item::setQuantity(int q)
{
    quantity = q;
}

void Item::showInfo()
{
    cout << name << " | 價格: " << cost << " | 目前已使用: " << quantity << " 個" << endl;
}

bool Item::isAvailable()
{
    return quantity > 0;
}

void Item::use()
{
    if (isAvailable()) {
        cout << "發動了物品增益: " << name << "!" << endl;
    }
}