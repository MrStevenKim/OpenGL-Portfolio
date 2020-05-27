#pragma once

#include "GameUI.h"

#include "Player.h"
#include "../game/menu.h"
#include "../game/stage.h"
#include "../game/endstage.h"
#include "../game/sceneManager.h"
#include "../game/vilege.h"
#include "Orc.h"

extern iStrTex* killIndicator;
extern iStrTex* timeIndicator;
extern Texture* playerPortrait;
extern iStrTex* hpIndicator;
extern iStrTex* mpIndicator;
extern iStrTex* staminaIndicator;
iPopup* PopPlayerInventory;
Texture* methodTimeIndicator(const char* str)
{
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(500, 50);

	setRGBA(1, 1, 1, 0);
	g->init(size);
	g->fillRect(0, 0, size.width, size.height);

	setRGBA(1, 1, 1, 1);
	setStringSize(50);
	setStringRGBA(1, 1, 0, 1);
	g->drawString(size.width / 2 - 50, size.height / 2, HCENTER | VCENTER, str);


	return g->getTexture();
}

Texture* methodKillIndicator(const char* str)
{
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(100, 50);

	setRGBA(1, 1, 1, 0);
	g->init(size);
	g->fillRect(0, 0, size.width, size.height);

	setRGBA(1, 1, 1, 1);
	setStringSize(50);
	setStringRGBA(1, 1, 0, 1);
	g->drawString(size.width / 2 - 50, size.height / 2, HCENTER | VCENTER, str);

	return g->getTexture();
}

Texture* methodPlayerHPIndicator(const char* str)
{
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(200, 50);

	setRGBA(1, 0, 0, 1);
	setStringSize(15);

	g->init(size);
	g->fillRect(0, 0, size.width * (hero->getHp() / hero->getMaxHp()), size.height);
	g->drawString(size.width / 2, size.height / 2, HCENTER | VCENTER, str);

	return g->getTexture();
}

Texture* methodPlayerMPIndicator(const char* str)
{
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(200, 50);

	setRGBA(0, 0, 1, 1);
	setStringSize(15);

	g->init(size);
	g->fillRect(0, 0, size.width * (hero->getMp() / hero->getMaxMP()), size.height);
	g->drawString(size.width / 2, size.height / 2, HCENTER | VCENTER, str);

	return g->getTexture();
}

Texture* methodPlayerStaminaIndicator(const char* str)
{
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(200, 50);

	setRGBA(1, 1, 0, 1);
	setStringSize(15);

	g->init(size);
	g->fillRect(0, 0, size.width * (hero->getStamina() / hero->getMaxStamina()), size.height);
	g->drawString(size.width / 2, size.height / 2, HCENTER | VCENTER, str);

	return g->getTexture();
}


//----------------PopPlayerUI------------------------//

iPopup* PopPlayerUI;
iImage** PopPlayerUIImgs;
Texture* Poptex;
iPopup* PopMenuUI;

//const char* slotString[5] = { "Name", "HP", "MP", "Stamina", "Menu" };

const char* mapTitle[1] = { "Waterfront" };
void createPopPlayerUI()
{
	iPopup* pop = new iPopup(iPopupStyleNone);
	iGraphics* g = iGraphics::instance();
	iImage* img = new iImage();
	iSize size = iSizeMake(devSize.width, devSize.height); // 크기를 화면크기랑 동일하게 사용자의 화면을 그래도 덮는 UI Layer

	PopPlayerUIImgs = (iImage**)malloc(sizeof(iImage*) * 6);


	// Stage Title
	{
		g->init(size);
		setStringRGBA(0, 0, 0, 1);
		setRGBA(1, 1, 1, 0);// alpha값은 0 투명한 사이즈의 화면크기의 상자를 만드는거니까
		g->fillRect(0, 0, devSize.width, devSize.height);
		g->drawString(devSize.width / 2, 10, HCENTER | VCENTER, "- Stage -");
		g->drawString(devSize.width / 2, 35, HCENTER | VCENTER, mapTitle[0]);
		g->drawString(devSize.width / 2, 65, HCENTER | VCENTER, "KILL:");

		Poptex = g->getTexture();
		img->addObject(Poptex);
		freeImage(Poptex);
		pop->addObject(img);
	}

	// kill indicator
	{
		setRGBA(1, 1, 1, 1);
		iImage* kill_indicator = new iImage();
		kill_indicator->addObject(killIndicator->tex);
		kill_indicator->position = iPointMake(devSize.width / 2, 90);
		pop->addObject(kill_indicator);
	}

	{ // 미니맵
		setRGBA(1, 1, 0, 1);
		setStringSize(10);
		iSize mapsize = iSizeMake(200, 200);
		//g->init(mapsize);
		//g->fillRect(0, 0, mapsize.width, mapsize.height);
		//g->drawString(mapsize.width / 2, mapsize.height / 2, HCENTER | VCENTER, "Minimap position");
		extern Texture* minimapFbo;
		Texture* minimapTex = minimapFbo; // g->getTexture();

		iImage* minimap = new iImage();
		minimap->leftRight = 2;
		minimap->addObject(minimapTex);
		minimap->position = iPointMake(devSize.width/2 +320, -60);
		pop->addObject(minimap);

	}

	// Stage Menu
	{
		setStringSize(30);
		iImage* menuBtn = new iImage();
		Texture* menuBtnTex;
		iSize menuSize = iSizeMake(200, 100);
		g->init(menuSize);
		setRGBA(0, 0, 1, 1);
		g->fillRect(0, 0, menuSize.width, menuSize.height);
		g->drawString(menuSize.width / 2, menuSize.height / 2, HCENTER | VCENTER, "Menu");

		menuBtnTex = g->getTexture();
		menuBtn->addObject(menuBtnTex);
		freeImage(menuBtnTex);

		menuBtn->position = iPointMake(devSize.width - menuSize.width, 10);
		PopPlayerUIImgs[0] = menuBtn;
		pop->addObject(menuBtn);

	}

	{
		iImage* playerImage = new iImage();
		iImage* playerName = new iImage();
		iImage* playerHP = new iImage();
		iImage* playerMP = new iImage();
		iImage* playerStamina = new iImage();

		Texture* infoTex;
		iSize infoSize = iSizeMake(200, 100);
		setRGBA(0, 1, 0, 1);

		// Player Portrait

		setRGBA(1, 1, 1, 1);
		playerImage->addObject(playerPortrait);
		playerImage->position = iPointMake(0, 10);
		PopPlayerUIImgs[1] = playerImage;
		pop->addObject(playerImage);

		// Player Name Indicator

		setStringSize(30);
		g->init(infoSize);
		g->drawString(infoSize.width / 2, infoSize.height / 2, HCENTER | VCENTER, "%s", hero->getName());
		infoTex = g->getTexture();
		playerName->addObject(infoTex);
		freeImage(infoTex);
		playerName->position = iPointMake(70, 15);
		pop->addObject(playerName);


		setRGBA(1, 1, 1, 1);
		playerHP->addObject(hpIndicator->tex);
		freeImage(hpIndicator->tex);
		playerHP->position = iPointMake(0, 110);
		PopPlayerUIImgs[2] = playerHP;
		pop->addObject(playerHP);

		playerMP->addObject(mpIndicator->tex);
		freeImage(mpIndicator->tex);
		playerMP->position = iPointMake(0, 160);
		PopPlayerUIImgs[3] = playerMP;
		pop->addObject(playerMP);

		playerStamina->addObject(staminaIndicator->tex);
		freeImage(staminaIndicator->tex);
		playerStamina->position = iPointMake(0, 210);
		PopPlayerUIImgs[4] = playerStamina;
		pop->addObject(playerStamina);

	}

	//Inventory Btn
	{
		setStringSize(30);
		iImage* Btn = new iImage();
		Texture* BtnTex;
		iSize BtnSize = iSizeMake(200, 100);
		g->init(BtnSize);
		setRGBA(0, 1, 0, 1);
		g->fillRect(0, 0, BtnSize.width, BtnSize.width);
		g->drawString(BtnSize.width / 2, BtnSize.height / 2, HCENTER | VCENTER, "Inventory");

		BtnTex = g->getTexture();
		Btn->addObject(BtnTex);
		freeImage(BtnTex);

		Btn->position = iPointMake(devSize.width - BtnSize.width, devSize.height - BtnSize.height);
		PopPlayerUIImgs[5] = Btn;
		pop->addObject(Btn);
		
	}

	pop->openPosition = iPointZero;
	pop->closePosition = iPointZero;

	PopPlayerUI = pop;
	setRGBA(1, 1, 1, 1);

}

void freePopPlayerUI()
{
	delete PopPlayerUI;
}

void drawPopPlayerUI(float dt)
{
	PopPlayerUI->paint(dt);
}

bool keyPopPlayerUI(iKeyState stat, iPoint point)
{

	int i, j = -1;

	switch (stat)
	{
	case iKeyState::iKeyStateBegan:
		i = PopPlayerUI->selected;

		if (i == -1)
			break;

		else if (i == 0)
		{
			printf("selected = %d\n", i);

			if (PopMenuUI->bShow == false)
				showPopMenuUI(true);

			else
				showPopMenuUI(false);
		}

		else if (i == 5)
		{
			if (PopPlayerInventory->bShow == false)
				showPopPlayerInventory(true);

			else
				showPopPlayerInventory(false);
		}

		else
			printf("seletecd = %d\n", i);
		break;

	case iKeyState::iKeyStateMoved:

		for (i = 0; i < 6; i++)
		{
			if (containPoint(point, PopPlayerUIImgs[i]->touchRect(PopPlayerUI->closePosition)))
			{
				j = i;
				break;
			}
		}
		PopPlayerUI->selected = j;
		break;

	case iKeyState::iKeyStateEnded:

		break;

	}

	return true;
}

void showPopPlayerUI(bool show)
{
	PopPlayerUI->show(show);
}



//--------------PopMenuUI---------------------/

//iPopup* PopMenuUI; PlayerUI 위에 선언해놨음.
iImage** PopMenuUIImgs;

const char* btnString[3] = { "Rusume Game", "Settings", "Game Quit" };

void createPopMenuUI()
{
	iPopup* pop = new iPopup(iPopupStyleAlpha);
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(500, 500);

	PopMenuUIImgs = (iImage**)malloc(sizeof(iImage*) * 3);

	// Background //
	{
		iImage* img = new iImage();
		Texture* tex;
		g->init(size);
		setStringRGBA(0, 0, 0, 1);
		setRGBA(1, 0, 1, 1);
		g->fillRect(0, 0, size.width, size.height);

		tex = g->getTexture();
		img->addObject(tex);
		freeImage(tex);
		img->position = iPointMake(0, 0);

		pop->addObject(img);
	}

	// buttons
	{
		setRGBA(0, 1, 1, 1);
		setStringRGBA(0, 0, 0, 1);
		setStringSize(20);

		iSize btnSize = iSizeMake(300, 30);

		for (int i = 0; i < 3; i++)
		{
			Texture* tex;
			iImage* btnImg = new iImage();

			g->init(btnSize);
			g->fillRect(0, 0, btnSize.width, btnSize.height);
			g->drawString(btnSize.width / 2, btnSize.height / 2, HCENTER | VCENTER, btnString[i]);

			tex = g->getTexture();
			btnImg->addObject(tex);
			freeImage(tex);

			btnImg->position = iPointMake((size.width - btnSize.width) / 2, i * 100 + 15);

			PopMenuUIImgs[i] = btnImg;
			pop->addObject(btnImg);

		}

	}

	// 메뉴창에 간단하게 게임 설명(목표) 넣는 부분

	pop->openPosition = iPointMake((devSize.width - size.width) / 2, (devSize.height - size.height) / 2);
	pop->closePosition = pop->openPosition;

	setRGBA(1, 1, 1, 1);

	PopMenuUI = pop;

}

void freePopMenuUI()
{
	delete PopMenuUI;

}

void drawPopMenuUI(float dt)
{
	PopMenuUI->paint(dt);
}

bool keyPopMenuUI(iKeyState stat, iPoint point)
{
	if (PopMenuUI->bShow == false)
		return false;

	if (PopMenuUI->stat != iPopupStatProc)
		return true;

	int i, j = -1;

	switch (stat)
	{
	case iKeyState::iKeyStateBegan:
	{
		i = PopMenuUI->selected;

		if (i == -1)
			break;

		else if (i == 0)
		{
			PopMenuUI->show(false);
		}

		else if (i == 1)
		{

		}

		else if (i == 2)
		{
			showPopQuitAnswerUI(true);
		}

		printf("seletecd = %d\n", i);
		break;
	}

	case iKeyState::iKeyStateMoved:
	{

		for (i = 0; i < 3; i++)
		{
			if (containPoint(point, PopMenuUIImgs[i]->touchRect(PopMenuUI->closePosition)))
			{
				j = i;
				break;
			}
		}
		PopMenuUI->selected = j;

		break;
	}
	case iKeyState::iKeyStateEnded:
	{
		break;
	}

	}

	return true;
}

void showPopMenuUI(bool show)
{
	PopMenuUI->show(show);
}


//----------------------PopQuitAnswerUI------------------------//

iPopup* PopQuitAnswerUI;
iImage** PopQuitAnswerUIBtn;
// 0 : yes,  1 : no
const char* btnUISlot[2] = { "Okay", "No" };
void createPopQuitAnswerUI()
{
	iPopup* pop = new iPopup(iPopupStyleAlpha);
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(500, 300);

	PopQuitAnswerUIBtn = (iImage**)malloc(sizeof(iImage*) * 2); // 0 : yes , 1 : no

	setStringBorder(0);
	setStringBorderRGBA(0, 0, 0, 1);
	setStringRGBA(0, 0, 0, 1);
	setStringSize(50);



	{ // background
		igImage* ig = g->createIgImage("assets/menu/popBg.png");
		size = iSizeMake(g->getIgImageWidth(ig) * 2.5, g->getIgImageHeight(ig) * 2.5);
		g->init(size);
		g->drawImage(ig, 0, 0, 2.5, 2.5, TOP | LEFT);
		g->drawString(size.width / 2, size.height / 2 - 175, VCENTER | HCENTER, "Do you want exit?");
		Texture* bgTex;

		bgTex = g->getTexture();

		iImage* bgImg = new iImage();
		bgImg->position = iPointMake(devSize.width / 2, devSize.height / 2);

		bgImg->addObject(bgTex);
		freeImage(bgTex);

		pop->addObject(bgImg);

	}

	for (int i = 0; i < 2; i++)
	{
		iImage* answerBtn = new iImage();
		Texture* btnTex;

		for (int j = 0; j < 2; j++)
		{
			if (j == 0) // btnOff
			{
				setRGBA(1, 1, 1, 1);
				setStringSize(30);
				igImage* answerBtn = g->createIgImage("assets/menu/BTN0.png");
				iSize btnSize = iSizeMake(g->getIgImageWidth(answerBtn), g->getIgImageHeight(answerBtn));
				g->init(btnSize);
				g->drawImage(answerBtn, 0, 0, 1, 1, TOP | LEFT);
				g->drawString(btnSize.width / 2, btnSize.height / 2, VCENTER | HCENTER, btnUISlot[i]);
				btnTex = g->getTexture();
			}

			else // btnOn
			{
				setRGBA(1, 0, 0, 1);
				setStringSize(30);
				igImage* answerBtn = g->createIgImage("assets/menu/BTN0.png");
				iSize btnSize = iSizeMake(g->getIgImageWidth(answerBtn), g->getIgImageHeight(answerBtn));
				g->init(btnSize);
				g->drawImage(answerBtn, 0, 0, 1, 1, TOP | LEFT);
				g->drawString(btnSize.width / 2, btnSize.height / 2, VCENTER | HCENTER, btnUISlot[i]);
				btnTex = g->getTexture();
			}

			answerBtn->addObject(btnTex);
			answerBtn->position = iPointMake(devSize.width / 2 * (i + 1) + 150, size.height + 10);
			freeImage(btnTex);
		}

		pop->addObject(answerBtn);

		PopQuitAnswerUIBtn[i] = answerBtn;

	}

	pop->openPosition = iPointMake(devSize.width / 2 - size.width - 100, devSize.height / 2 - size.height);
	pop->closePosition = pop->openPosition;
	PopQuitAnswerUI = pop;

}

void freePopQuitAnswerUI()
{
	delete PopQuitAnswerUI;
}

void drawPopQuitAnswerUI(float dt)
{
	PopQuitAnswerUI->paint(dt);
}

bool keyPopQuitAnswerUI(iKeyState stat, iPoint point)
{
	if (PopQuitAnswerUI->bShow == false)
		return false;

	if (PopQuitAnswerUI->stat != iPopupStatProc)
		return true;

	int i, j = -1;

	switch (stat)
	{
	case iKeyState::iKeyStateBegan:
	{
		i = PopQuitAnswerUI->selected;

		if (i == -1)
			break;

		if (i == 0)
		{
			extern bool runWnd;
			runWnd = false;

		}
		else if (i == 1)
		{
			PopQuitAnswerUI->show(false);
		}
		break;
	}

	case iKeyState::iKeyStateMoved:
	{
		for (i = 0; i < 2; i++)
		{
			if (containPoint(point, PopQuitAnswerUIBtn[i]->touchRect(PopQuitAnswerUI->closePosition)))
			{
				j = i;
				break;
			}
		}
		PopQuitAnswerUI->selected = j;
		break;
	}

	case iKeyState::iKeyStateEnded:
		break;
	}

	return true;
}

void showPopQuitAnswerUI(bool show)
{
	PopQuitAnswerUI->show(show);
}

struct Damage
{
	iStrTex* stDamage;
	iPoint p;
	float delta;

	bool paint(float dt, iPoint off);
};
#define Damage_delta 1.0f

Damage* _damage;
Damage** damage;
int damageNum;
#define _damageNum 100

Texture* methodStDamage(const char* str);

void loadNumber()
{
	_damage = (Damage*)malloc(sizeof(Damage) * _damageNum);
	for (int i = 0; i < _damageNum; i++)
	{
		Damage* d = &_damage[i];
		d->stDamage = new iStrTex(methodStDamage);
		d->p = iPointZero;
		d->delta = Damage_delta;
	}

	damage = (Damage**)malloc(sizeof(Damage*) * _damageNum);
	damageNum = 0;
}

void freeNumber()
{
	for (int i = 0; i < _damageNum; i++)
		delete _damage[i].stDamage;
	free(_damage);
	free(damage);
}
void drawNumber(float dt, iPoint off)
{
	for (int i = 0; i < damageNum; i++)
	{
		if (damage[i]->paint(dt, off))
		{
			damageNum--;
			for (int j = i; j < damageNum; j++)
				damage[j] = damage[1 + j];
			i--;
		}
	}
}
void addNumber(int dmg, iPoint position)
{
	for (int i = 0; i < _damageNum; i++)
	{
		Damage* d = &_damage[i];
		if (d->delta >= Damage_delta)
		{
			d->stDamage->setString("%d", dmg);
			d->p = position;
			d->delta = 0.0f;

			damage[damageNum] = d;
			damageNum++;
			return;
		}
	}
}

struct EffectHit
{
	iImage* img;
	iPoint p;
	int dir;

	bool paint(float dt, iPoint off)
	{
		img->paint(dt, p + off);
		img->leftRight = dir;
		if (img->animation)
			return false;
		return true;
	}
};
EffectHit** _ehEffectHit;
EffectHit** ehEffectHit;
int ehNum;
#define _ehNum 100

void loadEffectHit()
{
	int i;

	_ehEffectHit = (EffectHit**)malloc(sizeof(EffectHit*) * 1);

	iImage* img = new iImage();
	for (i = 0; i < 31; i++)
	{
		Texture* tex = createImage("assets/stage/hero/Knight/skill/hit/tile%d.png", i);
		img->addObject(tex);
		freeImage(tex);
	}
	img->position = iPointMake(-48, -48);
	img->_aniDt = 0.001f;
	img->_repeatNum = 1;

	_ehEffectHit[0] = (EffectHit*)malloc(sizeof(EffectHit) * _ehNum);
	for (i = 0; i < _ehNum; i++)
		_ehEffectHit[0][i].img = img->copy();

	delete img;

	ehEffectHit = (EffectHit**)malloc(sizeof(EffectHit*) * 1 * _ehNum);
	ehNum = 0;
}

void freeEffectHit()
{
	for (int j = 0; j < 1; j++)
	{
		for (int i = 0; i < _ehNum; i++)
			delete _ehEffectHit[j][i].img;
		free(_ehEffectHit[j]);
	}
	free(_ehEffectHit);
	free(ehEffectHit);
}

void drawEffectHit(float dt, iPoint off)
{
	setRGBA(1, 0, 0, 1);
	for (int i = 0; i < ehNum; i++)
	{
		if (ehEffectHit[i]->paint(dt, off))
		{
			ehNum--;
			for (int j = i; j < ehNum; j++)
				ehEffectHit[j] = ehEffectHit[1 + j];
		}
	}
	setRGBA(1, 1, 1, 1);
}

void addEffectHit(int index, iPoint p)
{
	for (int i = 0; i < _ehNum; i++)
	{
		EffectHit* eh = &_ehEffectHit[index][i];
		if (eh->img->animation == false)
		{
			eh->p = p;
			eh->dir = 0;
			eh->img->startAnimation();

			ehEffectHit[ehNum] = eh;
			ehNum++;
			return;
		}
	}
}

extern Monster** orcs;
struct Projectile
{
	iImage* img;
	iPoint p;
	int dir;
	int speed;
	iSize rectSize = iSizeMake(32, 32);

	bool paint(float dt, iPoint off)
	{
	
		if (dir == 1)
			p += iPointMake(1, 0) * speed;
		else
			p += iPointMake(-1, 0) * speed;
		img->paint(dt, p + off);
		img->leftRight = dir;

		extern int gameState;

		if (gameState == gs_stage)
		{
			for (int i = 0; i < 10; i++)
			{

				if (containPoint(iPointMake(p.x, p.y + 32), iRectMake(orcs[i]->position.x, orcs[i]->position.y, 64, 64)))
				{
					((Orc*)orcs[i])->setDmg(15);
					addEffectHit(0, orcs[i]->position);
					zoomCamera(orcs[i]->position, 1.5);
					return true;
				}
			}
		}
		else if (gameState == gs_stage)
		{

		}
		
		//else if (gameState == gs_boss)
		//{

		//}

		
		if (img->animation)
			return false;


		return true;

	}
};

Projectile** _projectile;
Projectile** projectile;
int projectNum;
#define _projectNum 100

void loadProjectile()
{
	int i;
	_projectile = (Projectile**)malloc(sizeof(Projectile*) * 1);
	 
	iImage* img = new iImage();
	for (int i = 0; i < 61; i++)
	{
		Texture* tex = createImage("assets/stage/hero/Knight/skill2/tile%03d.png", i);
		img->addObject(tex);
		freeImage(tex);
	}
	img->position = iPointMake(-60, -60);
	img->_aniDt = 0.01f;
	img->_repeatNum = 0;

	_projectile[0] = (Projectile*)malloc(sizeof(Projectile) * _projectNum);
	for (i = 0; i < _projectNum; i++)
		_projectile[0][i].img = img->copy();

	delete img;

	projectile = (Projectile**)malloc(sizeof(Projectile*) * 1 * _projectNum);
	projectNum = 0;


}

void freeProjectile()
{
	for (int j = 0; j < 1; j++)
	{
		for (int i = 0; i < _projectNum; i++)
			delete _projectile[j][i].img;

		free(_projectile[j]);
	}
	free(_projectile);
	free(projectile);
}



void drawProjectile(float dt, iPoint off)
{
	for (int i = 0; i < projectNum; i++)
	{
		if (projectile[i]->paint(dt, off))
		{
			projectNum--;
			for (int j = i; j < projectNum; j++)
				projectile[j] = projectile[1 + j];
		}

	}
}

void addProjectile(int index, iPoint p,int direction, int speed)
{
	for (int i = 0; i < _projectNum; i++)
	{
		Projectile* pj = &_projectile[index][i];
		if (pj->img->animation == false)
		{
			pj->p = p;
			pj->dir = direction;
			pj->speed = speed;
			pj->img->startAnimation();

			projectile[projectNum] = pj;
			projectNum++;
			return;
		}

	}
}

//------------PopGameOverUI---------------//

iPopup* PopGameOver;
iImage** GameOverBtn;
const char* btnStr[2] = { "MainMenu", "Game Quit" };

void createPopGameOverUI()
{
	iPopup* pop = new iPopup(iPopupStyleAlpha);
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(devSize.width, devSize.height);
	setRGBA(1, 0, 0, 1);
	fillRect(0, 0, devSize.width, devSize.height);


	GameOverBtn = (iImage**)malloc(sizeof(iImage*) * 2); // 0 : 메인메뉴 1 : 게임종료

	// gameOverTitle
	{
		setStringSize(30);
		setRGBA(1, 0, 0, 1);
		iSize titleSize = iSizeMake(devSize.width, devSize.height);
		g->init(titleSize);
		g->fillRect(0, 0, devSize.width, devSize.height);
		g->drawString(titleSize.width / 2, titleSize.height / 2, HCENTER | VCENTER, "You die......!");
		Texture* overTitleTex;
		overTitleTex = g->getTexture();

		iImage* overTitle = new iImage();
		overTitle->addObject(overTitleTex);
		overTitle->position = iPointMake(devSize.width / 2, devSize.height / 2);

		freeImage(overTitleTex);

		pop->addObject(overTitle);
	}

	for (int i = 0; i < 2; i++)
	{
		iImage* answerBtn = new iImage();
		Texture* btnTex;

		for (int j = 0; j < 2; j++)
		{
			if (j == 0) // off
			{
				setRGBA(1, 1, 1, 1);
				setStringSize(15);
				igImage* answerBtn = g->createIgImage("assets/menu/BTN0.png");
				iSize btnSize = iSizeMake(g->getIgImageWidth(answerBtn), g->getIgImageHeight(answerBtn));
				g->init(btnSize);
				g->drawImage(answerBtn, 0, 0, 1, 1, TOP | LEFT);
				g->drawString(btnSize.width / 2, btnSize.height / 2, VCENTER | HCENTER, btnStr[i]);
				btnTex = g->getTexture();
			}

			else // on
			{
				setRGBA(1, 0, 0, 1);
				setStringSize(15);
				igImage* answerBtn = g->createIgImage("assets/menu/BTN0.png");
				iSize btnSize = iSizeMake(g->getIgImageWidth(answerBtn), g->getIgImageHeight(answerBtn));
				g->init(btnSize);
				g->drawImage(answerBtn, 0, 0, 1, 1, TOP | LEFT);
				g->drawString(btnSize.width / 2, btnSize.height / 2, VCENTER | HCENTER, btnStr[i]);
				btnTex = g->getTexture();
			}

			answerBtn->addObject(btnTex);
			answerBtn->position = iPointMake(devSize.width / 2 * (i + 1) + 150, size.height + 10);
			freeImage(btnTex);
		}

		pop->addObject(answerBtn);

		GameOverBtn[i] = answerBtn;
	}

	pop->openPosition = iPointMake(devSize.width / 2 - size.width, devSize.height / 2 - size.height);
	pop->closePosition = pop->openPosition;

	PopGameOver = pop;
}

void freePopGameOverUI()
{
	delete PopGameOver;
}

void drawPopGameOverUI(float dt)
{
	PopGameOver->paint(dt);
}

bool keyPopGameOverUI(iKeyState stat, iPoint point)
{
	if (PopGameOver->bShow == false)
		return false;

	if (PopGameOver->stat != iPopupStatProc)
		return true;

	int i, j = -1;

	switch (stat)
	{
	case iKeyState::iKeyStateBegan:
	{
		i = PopGameOver->selected;

		if (i == -1)
			break;

		if (i == 0)
		{
			switch (gameState)
			{
			case gs_stage:
				setLoading(gs_menu, freeStage, loadMenu);
				break;

			case gs_endStage:
				setLoading(gs_menu, freeEndStage, loadMenu);
				break;

			}
		}

		else if (i == 1)
		{
			extern bool runWnd;
			runWnd = false;
		}
		break;
	}

	case iKeyState::iKeyStateMoved:
	{
		for (i = 0; i < 2; i++)
		{
			if (containPoint(point, GameOverBtn[i]->touchRect(PopGameOver->closePosition)))
			{
				j = i;
				break;
			}
		}

		PopGameOver->selected = j;
		break;
	}

	case iKeyState::iKeyStateEnded:
		break;

	}

	return true;
}

void showPopGameOverUI(bool show)
{
	PopGameOver->show(show);
}

//-----------------PopStageNPCMenuUI---------------------//

iPopup* PopStageNPCMenuUI;
iImage** PopStageNPCMenuUIImgs;

const char* StageNPCStr[2] = { "Yes", "No" };

void createPopStageNPCMenuUI()
{
	iPopup* pop = new iPopup(iPopupStyleAlpha);
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(700, 300);

	PopStageNPCMenuUIImgs = (iImage**)malloc(sizeof(iImage*) * 2);

	setStringBorder(0);
	setStringBorderRGBA(0, 0, 0, 1);
	setStringRGBA(0, 0, 0, 1);
	setStringSize(30);


	// Background //
	{
		iImage* img = new iImage();
		Texture* tex;
		setRGBA(0, 1, 1, 1);
		g->init(size);
		g->fillRect(0, 0, size.width, size.height);
		g->drawString(size.width / 2, 30, HCENTER | VCENTER, "Would you like to enter the village?");

		tex = g->getTexture();
		img->addObject(tex);
		freeImage(tex);
		img->position = iPointMake(0, 0);

		pop->addObject(img);
	}

	// button //
	{
		setRGBA(1, 0, 0, 1);
		setStringSize(15);

		iSize btnSize = iSizeMake(150, 30);

		for (int i = 0; i < 2; i++)
		{
			iImage* answerBtn = new iImage();
			Texture* btnTex;

			for (int j = 0; j < 2; j++)
			{
				if (j == 0) // btnoff
				{
					setRGBA(0, 1, 0, 1);
					g->init(btnSize);
					g->fillRect(0, 0, btnSize.width, btnSize.height);
					g->drawString(btnSize.width / 2, btnSize.height / 2, VCENTER | HCENTER, StageNPCStr[i]);
					btnTex = g->getTexture();
				}

				else // btnon
				{
					setRGBA(1, 0, 0, 1);
					g->init(btnSize);
					g->fillRect(0, 0, btnSize.width, btnSize.height);
					g->drawString(btnSize.width / 2, btnSize.height / 2, VCENTER | HCENTER, StageNPCStr[i]);
					btnTex = g->getTexture();
				}
				answerBtn->addObject(btnTex);
				answerBtn->position = iPointMake(200 * i + 150, size.height / 2 + 20);
				freeImage(btnTex);
			}

			pop->addObject(answerBtn);

			PopStageNPCMenuUIImgs[i] = answerBtn;

		}

	}


	pop->openPosition = iPointMake(devSize.width / 2 - size.width / 2, devSize.height / 2 - size.height / 2);
	pop->closePosition = pop->openPosition;


	PopStageNPCMenuUI = pop;
}

void freePopStageNPCMenuUI()
{

	free(PopStageNPCMenuUIImgs);

	// iPopup delete시 안에 있는 Img들 다 메모리 해제함

	delete PopStageNPCMenuUI;

}

void drawPopStageNPCMenuUI(float dt)
{
	PopStageNPCMenuUI->paint(dt);
}

bool keyPopStageNPCMenuUI(iKeyState stat, iPoint point)
{
	if (PopStageNPCMenuUI->bShow == false)
		return false;

	if (PopStageNPCMenuUI->stat != iPopupStatProc)
		return true;

	int i, j = -1;

	switch (stat)
	{
	case iKeyState::iKeyStateBegan:
	{
		i = PopStageNPCMenuUI->selected;

		if (i == -1)
			break;

		if (i == 0)
		{
			
			setLoading(gs_villege, freeEndStage, loadVillege);

		}
		else if (i == 1)
		{
			
			PopStageNPCMenuUI->show(false);
		}
		break;
	}
	case iKeyState::iKeyStateMoved:
	{
		for (i = 0; i < 2; i++)
		{
			if (containPoint(point, PopStageNPCMenuUIImgs[i]->touchRect(PopStageNPCMenuUI->closePosition)))
			{
				j = i;
				break;
			}
		}
		PopStageNPCMenuUI->selected = j;
		break;
	}
	}
	return true;
}

void showPopStageNPCMenuUI(bool show)
{
	PopStageNPCMenuUI->show(show);
}

//----------------PopPlayerInventory------------------//
//iPopup* PopPlayerInventory; 맨위에 선언함
iImage** PopPlayerInventoryImgs;
void createPopPlayerInventory()
{
	iPopup* pop = new iPopup(iPopupStyleAlpha);
	iGraphics* g = iGraphics::instance();

	iSize bgSize = iSizeMake(700, 300);
	PopPlayerInventoryImgs = (iImage**)malloc(sizeof(iImage*) * 20); // 임시로 20개 만듬

	//Inventory background
	{
		iImage* img = new iImage();
		Texture* tex; 
		setRGBA(1, 1, 1, 1);
		g->init(bgSize);
		g->fillRect(0, 0, bgSize.width, bgSize.height);
		g->drawString(bgSize.width / 2, 20, HCENTER | VCENTER, "%s Inventory", hero->getName());
		tex = g->getTexture();
		img->addObject(tex);
		freeImage(tex);
		img->position = iPointZero;
		pop->addObject(img);	
	}

	// Equitment
	{
		iSize size = iSizeMake(250, 250);
		iImage* img = new iImage();
		Texture* tex;
		setRGBA(1, 0, 0, 1);
		g->init(size);
		g->fillRect(0, 0, size.width, size.height);
		g->drawString(size.width / 2, 10, HCENTER|VCENTER, "Enquitment");
		tex = g->getTexture();
		img->addObject(tex);
		freeImage(tex);
		img->position = iPointMake(10, 35);
		pop->addObject(img);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				iSize rectSize = iSizeMake(64, 64);
				iImage* rectImg = new iImage();
				Texture* rectTex;
				setRGBA(1, 1, 0, 1);
				g->init(rectSize);
				g->fillRect(0, 0, rectSize.width, rectSize.height * (i + 1));

				rectTex = g->getTexture();
				rectImg->addObject(rectTex);
				freeImage(rectTex);
				rectImg->position = iPointMake(size.width / 2 - rectSize.width + (100 * j), size.height / 2 - rectSize.height/2 + (100 * i));
				pop->addObject(rectImg);
			}
		}


	}
	//bags
	{
		iSize size = iSizeMake(250, 250);
		iImage* img2 = new iImage();
		Texture* tex2;
		setRGBA(0, 1, 0, 1);
		g->init(size);
		g->fillRect(0, 0, size.width, size.height);
		g->drawString(size.width / 2, 10, HCENTER | VCENTER, "Bags");
		tex2 = g->getTexture();
		img2->addObject(tex2);
		freeImage(tex2);
		img2->position = iPointMake(bgSize.width - size.width - 10, 35);
		pop->addObject(img2);

		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				iSize rectSize = iSizeMake(64, 64);
				iImage* rectImg2 = new iImage();
				Texture* rectTex2;
				setRGBA(1, 1, 1, 1);
				g->init(rectSize);
				g->fillRect(0, 0, rectSize.width, rectSize.height * (i + 1));

				rectTex2 = g->getTexture();
				rectImg2->addObject(rectTex2);
				freeImage(rectTex2);
				rectImg2->position = iPointMake(size.width / 2 - rectSize.width + (100 * j)+ 420, size.height / 2 - rectSize.height / 2 + (100 * i));
				pop->addObject(rectImg2);
			}
		}
	}

	// Money
	{
		iSize size = iSizeMake(100, 100);
		iImage* img = new iImage();
		Texture* tex;
		setRGBA(0, 0, 1, 1);
		g->init(size);
		g->fillRect(0, 0, size.width, size.height);
		g->drawString(size.width / 2, 10, HCENTER | VCENTER, "Money");
		tex = g->getTexture();
		img->addObject(tex);
		freeImage(tex);
		img->position = iPointMake(bgSize.width / 2 - size.width / 2, 35);
		pop->addObject(img);
	}




	

	
	pop->openPosition = iPointMake(devSize.width / 2 - bgSize.width / 2, devSize.height / 2 - bgSize.height / 2);
	pop->closePosition = pop->openPosition;
	PopPlayerInventory = pop;
}

void freePopPlayerInventory()
{
	delete PopPlayerInventory;
}

void drawPopPlayerInventory(float dt)
{
	PopPlayerInventory->paint(dt);
}

bool keyPopPlayerInventory(iKeyState stat, iPoint point)
{
	return true;
}

void showPopPlayerInventory(bool show)
{
	PopPlayerInventory->show(show);
}

Texture* methodStDamage(const char* str)
{
	iGraphics* g = iGraphics::instance();
	iSize size = iSizeMake(100, 20);

	setRGBA(1, 1, 1, 0);
	g->init(size);
	g->fillRect(0, 0, size.width, size.height);

	setRGBA(1, 1, 1, 1);
	setStringSize(20);
	setStringRGBA(1, 0, 0, 1);
	g->drawString(size.width / 2, size.height / 2, HCENTER | VCENTER, str);


	return g->getTexture();

}

bool Damage::paint(float dt, iPoint off)
{
	float r = delta / Damage_delta;
	iPoint pp = p + off + iPointMake(0, -easeIn(r, 0, 200));
	float a = 1.0f - r;
	setRGBA(1, 1, 1, a);
	stDamage->paint(pp.x, pp.y, VCENTER | HCENTER);
	setRGBA(1, 1, 1, 1);

	delta += dt;
	if (delta < Damage_delta)
		return false;
	return true;
}

