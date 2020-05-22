#pragma once
#include "iStd.h"

// 여기에 플레이어의 체력, 게임 플레이상의 UI 출력해야함 

//-------------PopPlayerUI----------------------//
void createPopPlayerUI();
void freePopPlayerUI();
void drawPopPlayerUI(float dt);
bool keyPopPlayerUI(iKeyState stat, iPoint point);
void showPopPlayerUI(bool show);

//------------PopMenuUI------------------------// 
void createPopMenuUI();
void freePopMenuUI();
void drawPopMenuUI(float dt);
bool keyPopMenuUI(iKeyState stat, iPoint point);
void showPopMenuUI(bool show);

//------------PopQuitAnswerUI------------------//
void createPopQuitAnswerUI();
void freePopQuitAnswerUI();
void drawPopQuitAnswerUI(float dt);
bool keyPopQuitAnswerUI(iKeyState stat, iPoint point);
void showPopQuitAnswerUI(bool show);

//------------Number------------------//
void loadNumber();
void freeNumber();
void drawNumber(float dt, iPoint off);
void addNumber(int dmg, iPoint position);


//-------------PopGameOverUI---------------------//
void createPopGameOverUI();
void freePopGameOverUI();
void drawPopGameOverUI(float dt);
bool keyPopGameOverUI(iKeyState stat, iPoint point);
void showPopGameOverUI(bool show);