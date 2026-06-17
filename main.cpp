#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#include "Item.h"
#include "Skill.h"
#include "Player.h"
#include "Monster.h"

using namespace std;

int main()
{
    srand(time(NULL));

    string user_name;
    cout << "請輸入您的大名 > ";
    cin >> user_name;
    cout << endl << user_name << "您好 !!!"<<endl;

    cout << "==================================" << endl;
    cout << "        歡迎來到文字RPG !!!        " << endl;
    cout << "       這是一個勇者的故事...        " << endl;
    cout << "==================================" << endl;

    // 選擇職業
    int classChoice;
    cout << user_name << "請選擇你的職業:\n(1) 戰士 (HP:100, Atk:20, MP:120)\n(2) 射手 (HP:75, Atk:30, MP:100)\n(3) 法師 (HP:50, Atk:40, MP:80)\n> ";
    cin >> classChoice;

    Player* player = nullptr;
    if (classChoice == 1)
    {
        player = new Player("戰士", 100, 20, 120);
        player->addSkill(Skill("劈砍", 30, 30));
        player->addSkill(Skill("正義之劍", 50, 50));
    }
    else if (classChoice == 2)
    {
        player = new Player("射手", 75, 30, 100);
        player->addSkill(Skill("一箭穿心", 40, 25)); 
        player->addSkill(Skill("萬箭齊發", 60, 40));
    }
    else
    {
        player = new Player("法師", 50, 40, 80);
        player->addSkill(Skill("火球", 60, 20));
        player->addSkill(Skill("迷幻法陣", 70, 35));
    }

    player->initInventory();// 初始化item
    
    return(0);
}
