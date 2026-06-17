#include "Player.h"
#include "Monster.h"
#include <iostream>
#include <cstdlib>

using namespace std;

Player::Player(string n, int h, int atk, int m) : name(n), hp(h), maxHp(h), attackPower(atk), mp(m), maxMp(m), gold(0) {}

string Player::getName()
{
    return name;
}
int Player::getHp()
{
    return hp;
}
int Player::getGold()
{
    return gold;
}

void Player::addGold(int g)
{
    gold += g;
}
void Player::deductGold(int g)
{
    gold -= g;
}
void Player::addSkill(Skill s)
{
    skills.push_back(s);
}

void Player::initInventory()
{
    items.push_back(Item("能量飲尿", "MP_REGEN", 20, 10, 0));
    items.push_back(Item("麻辣加血", "HP_BUFF", 15, 20, 0));
    items.push_back(Item("超級馬力", "ATK_BUFF", 20, 30, 0));
}

int Player::getItemQuantity(string itemName)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getName() == itemName)
        {
            return items[i].getQuantity();
        }
    }
    return 0;
}

void Player::buyItem(string itemName)
{
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getName() == itemName)
        {
            items[i].addQuantity(1); 
            if (itemName == "麻辣加血")
            {
                maxHp += 20;
                hp += 20; 
                cout << "【提示】麻辣加血購買成功！最大血量提升 20 ! 目前最大血量: " << maxHp << endl;
            }
            return;
        }
    }
}

void Player::takeDirectDamage(int damage)
{
    hp -= damage;
    if (hp < 1) hp = 1; 
    cout << name << " 扣除了 " << damage << " 點 HP ! (目前 HP: " << hp << "/" << maxHp << ")" << endl;
}

void Player::reduceMaxHp(int amount)
{
    maxHp -= amount;
    if (maxHp < 1) maxHp = 1;
    if (hp > maxHp) hp = maxHp;
    cout << name << " 的最大血量減少了 " << amount << " 點！(目前最大 HP: " << maxHp << ")" << endl;
}

void Player::loseRandomItem()
{
    vector<int> availableIndices;
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].getQuantity() > 0)
        {
            availableIndices.push_back(i);
        }
    }
    
    if (!availableIndices.empty())
    {
        int dropIndex = availableIndices[rand() % availableIndices.size()];
        items[dropIndex].addQuantity(-1);
        cout << "糟糕！被小偷偷走了 1 個【" << items[dropIndex].getName() << "】！" << endl;
    }
    else
    {
        cout << "小偷翻了翻你的包包，發現你窮得連一個道具都沒有，留下同情的眼淚後離開了。" << endl;
    }
}

void Player::attack(Monster& target)
{
    cout << "\n>>> " << name << " 發動了普通攻擊！" << endl;
    target.takeDamage(attackPower);
}

bool Player::useSkill(int skillIndex, Monster& target)
{
    if (skillIndex >= 0 && skillIndex < skills.size())
    {
        Skill& s = skills[skillIndex];
        if (mp >= s.getMpCost())
        {
            mp -= s.getMpCost();
            cout << "\n>>> " << name << " ";
            s.use(mp, maxMp);
            target.takeDamage(s.getDamage());
            return true; 
        }
        else
        {
            cout << "\n[警告] 魔力不足 (" << mp << "/" << s.getMpCost() << ")，無法施放該技能！請重新選擇。" << endl;
            return false; 
        }
    }
    return false; 
}

void Player::takeDamage(int damage)
{
    hp -= damage;
    if (hp < 0) hp = 0;
    cout << name << " 受到了 " << damage << " 點傷害！(剩餘血量: " << hp << "/" << maxHp << ")" << endl;
}

void Player::useItem()
{
    bool hasAnyItem = false;
    for (int i = 0; i < items.size(); i++)
    {
        if (items[i].isAvailable())
        {
            if (!hasAnyItem)
            {
                cout << "\n--- 結算回合物品增益 ---" << endl;
                hasAnyItem = true;
            }
            items[i].use();
            int totalEffect = items[i].getEffectValue() * items[i].getQuantity();
            
            if (items[i].getType() == "MP_REGEN")
            {
                mp += totalEffect;
                if (mp > maxMp) mp = maxMp; 
                cout << "  -> 恢復了 " << totalEffect << " 點魔力！(目前 MP: " << mp << "/" << maxMp << ")" << endl;
            }
            else if (items[i].getType() == "HP_BUFF")
            {
                hp += totalEffect;
                if (hp > maxHp) hp = maxHp; 
                cout << "  -> 恢復了 " << totalEffect << " 點血量！(目前 HP: " << hp << "/" << maxHp << ")" << endl;
            }
            else if (items[i].getType() == "ATK_BUFF")
            {
                attackPower += totalEffect;
                cout << "  -> 攻擊力提升了 " << totalEffect << " 點！(目前 攻擊力: " << attackPower << ")" << endl;
            }
        }
    }
}

bool Player::isAlive()
{
    return hp > 0;
}

void Player::showStatus()
{
    cout << "\n==================================" << endl;
    cout << "[玩家狀態] " << name << " | HP: " << hp << "/" << maxHp 
         << " | MP: " << mp << "/" << maxMp << " | 攻擊: " << attackPower << " | 金幣: " << gold << endl;
    
    cout << "[持有道具] ";
    for (int i = 0; i < items.size(); i++) {
        cout << items[i].getName() << ": " << items[i].getQuantity() << "個";
        if (i < items.size() - 1) cout << " | ";
    }
    cout << endl;

    cout << "--- 技能 ---" << endl;
    for (int i = 0; i < skills.size(); i++) {
        cout << "  (" << i+1 << ") ";
        skills[i].showInfo();
    }
    cout << "==================================" << endl;
}