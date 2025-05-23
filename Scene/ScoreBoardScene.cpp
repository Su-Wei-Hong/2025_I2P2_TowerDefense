#include"ScoreBoardScene.hpp"
#include "Engine/GameEngine.hpp"
#include "UI/Component/ImageButton.hpp"
#include "UI/Component/Label.hpp"
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
std::map<std::string,int> record;
std::vector<std::pair<std::string,int>> temp;
int cur_page = 1;
int max_page = 0;
int w,h,halfW,halfH;
float lineSpacing = 40; 
float startX = 400;  // Adjust this to center or align left
float startY = 150;  // Starting Y position
void ScoreBoardScene::Initialize(){
    record.clear();
    w = Engine::GameEngine::GetInstance().GetScreenSize().x;
    h = Engine::GameEngine::GetInstance().GetScreenSize().y;
    halfW = w / 2;
    halfH = h / 2;
    AddNewObject(new Engine::Label("Score Board", "pirulen.ttf", 60, halfW, halfH * 1 / 6 , 10, 255, 255, 255, 0.5, 0.5));
    Engine::ImageButton *btn;
    std::ifstream fin("Resource/scoreboard.txt");
    std::string name;
    int score;
    
    int maxline = 12;
    if (!fin.is_open()) {
        std::cout << "Failed to open scoreboard.txt\n";
        return;
    }
    while (fin>>name>>score) {
        temp.push_back({name,score});
        // std::stringstream ss;
        // ss << std::left << std::setw(20) << name << std::right << std::setw(4) << score;
        // Create a label for each line and add it to the scene
    }
    for(int j=temp.size()-1;j>0;j--){
        for(int i=0;i<j;i++){
            if(temp[i].second<temp[i+1].second){
                auto a = temp[i];
                temp[i] = temp[i+1];
                temp[i+1] = a;
            }
        }
    }
    int b = temp.size()>12?12:temp.size();
    max_page = temp.size()/12 + 1;
    for(int i=0;i<b;i++){
        // AddNewObject(new Engine::Label(
        //     temp[i].first, "pirulen.ttf", 32,
        //     halfW-225, startY + i * lineSpacing,
        //     255, 255, 255, 255, 0.0, 0.0));

        // AddNewObject(new Engine::Label(
        //     std::to_string(temp[i].second), "pirulen.ttf", 32,
        //     halfW+200, startY + i * lineSpacing,
        //     255, 255, 255, 255, 1, 0.0));

        std::cout << i <<" ";
    }
    fin.close();
    btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    btn->SetOnClickCallback(std::bind(&ScoreBoardScene::BackOnClick, this, 2));
    AddNewControlObject(btn);
    AddNewObject(new Engine::Label("Back", "pirulen.ttf", 48, halfW, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    // btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW - 200, halfH * 7 / 4 - 50, 400, 100);
    // btn->SetOnClickCallback(std::bind(&ScoreBoardScene::Update, this, -1));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("prev page", "pirulen.ttf", 48, halfW-200, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));

    // btn = new Engine::ImageButton("win/dirt.png", "win/floor.png", halfW + 200, halfH * 7 / 4 - 50, 400, 100);
    // btn->SetOnClickCallback(std::bind(&ScoreBoardScene::Update, this, 1));
    // AddNewControlObject(btn);
    // AddNewObject(new Engine::Label("next page", "pirulen.ttf", 48, halfW+200, halfH * 7 / 4, 0, 0, 0, 255, 0.5, 0.5));
}
void ScoreBoardScene::Terminate(){
    IScene::Terminate();
}
void ScoreBoardScene::Update(int a){
    if(cur_page+a<0){
        return;
    }
    else if(cur_page+a>max_page){
        return;
    }
    else{
        cur_page += a;
        int b = cur_page<max_page?12:temp.size()%12;
        if(b==0){
            b = 12;
        }
        for(int i=0;i<b;i++){
            int index = 12*(cur_page-1) + i;
        AddNewObject(new Engine::Label(
            temp[index].first, "pirulen.ttf", 32,
            halfW-225, startY + i * lineSpacing,
            255, 255, 255, 255, 0.0, 0.0));

        AddNewObject(new Engine::Label(
            std::to_string(temp[index].second), "pirulen.ttf", 32,
            halfW+200, startY + i * lineSpacing,
            255, 255, 255, 255, 1, 0.0));
        }
        return;

    }
}
void ScoreBoardScene::BackOnClick(int stage){
    Engine::GameEngine::GetInstance().ChangeScene("stage-select");
}