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

    //設定怪物陣容
    vector<Monster> monsters= 
    {
        Monster("哥布林",60,10,10),
        Monster("哥布林長老",70,15,20),
        Monster("石頭人",80,20,20),
        Monster("閃電鳥",100,30,20),
        Monster("哥吉拉",150,50,0)
    };

    vector<Item> shopItems= 
    {
        Item("能量飲尿","MP_REGEN",20,10),
        Item("麻辣加血","HP_BUFF",15,20),
        Item("超級馬力","ATK_BUFF",20,30)
    };

    //遊戲主迴圈
    for (int stage = 0; stage < monsters.size(); stage++) 
    {
        Monster& currentMonster = monsters[stage];
        cout << "\n\n>>>>>>>> 第 " << stage + 1 << " 輪戰鬥開始 <<<<<<<<" << endl;
        
        if (stage == 0) 
        {
            cout << "【劇情】微風吹過新手村外的樹林，一隻流著口水的哥布林從草叢裡跳了出來！" << endl;
        } 
        else if (stage == 1) 
        {
            cout << "【劇情】你繼續深入叢林，四周的光線變得昏暗。一隻拄著法杖、眼神狡黠的哥布林長老擋住了你的去路！" << endl;
        } 
        else if (stage == 2) 
        {
            cout << "【劇情】穿過危險的叢林，你來到了荒蕪的山腳下。突然，腳下的巨石開始劇烈震動，一個巨大的石頭人站了起來！" << endl;
        }
        else if (stage == 3) 
        {
            cout << "【劇情】你辛苦地爬到了半山腰，四周雷聲大作。伴隨著刺眼的閃光，一隻渾身帶電的閃電鳥從烏雲中俯衝而下！" << endl;
        }
        else if (stage == 4)
        {
            cout << "【劇情】終於登上了山頂！火山口冒著濃煙，伴隨著震耳欲聾的咆哮，終極 Boss 哥吉拉帶著毀滅的氣息出現在你面前！" << endl;
        }
        cout << "遭遇了怪物: " << currentMonster.getName() << " ! " << endl;

        
    return(0);
}
