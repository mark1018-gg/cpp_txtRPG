#include "Monster.h"
#include "Player.h"
#include <iostream>
using namespace std;

Monster::Monster(string n,int h,int atk,int gold):name(n),hp(h),attackPower(atk),rewardGold(gold){}

string Monster::getName()
{ 
    return name;
}
int Monster::getRewardGold()
{ 
    return rewardGold; 
}
int Monster::getHp()
{ 
    return hp;
}

void Monster::attack(Player& p)
{
    cout<<"\n<<< "<<name<<" 發動了攻擊！"<<endl;
    p.takeDamage(attackPower);
}

void Monster::takeDamage(int damage) 
{
    hp-=damage;
    if(hp < 0)
    {
        hp = 0;
    }
    cout<<name<<" 受到了 "<<damage<<" 點傷害！(剩餘血量: " << hp << ")"<<endl;
}

bool Monster::isAlive()
{
    return hp>0;
}

void Monster::showInfo() 
{
    cout<<"【怪物】" <<name<<" | HP: " << hp << " | 攻擊力: "<<attackPower<<endl;
}