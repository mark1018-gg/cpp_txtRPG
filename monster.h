#ifndef MONSTER_H
#define MONSTER_H
#include <string>

class Player; 

class Monster
{
    private:
        std::string name;
        int hp;
        int attackPower;
        int rewardGold;

    public:
        Monster(std::string n,int h,int atk,int gold);

        std::string getName();
        int getRewardGold();
        int getHp();

        void attack(Player& p); 
        void takeDamage(int damage);
        bool isAlive();
        void showInfo();
};

#endif