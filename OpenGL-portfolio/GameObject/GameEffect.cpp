#pragma once

#include "GameEffect.h"
#include "../game/sceneManager.h"
#include "Goblin.h"

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
		img->leftRight =  dir;
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

	_ehEffectHit = (EffectHit**)malloc(sizeof(EffectHit*) * 2);

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

	setRGBA(1, 1, 1, 1);
	img = new iImage();
	for (i = 1; i < 20; i++)
	{
		Texture* tex = createImage("assets/stage/ghostwarrior/colisioneffect/eff (%d).png", i);
		tex->width *= 0.7f;
		tex->height *= 0.7f;
		tex->potWidth *= 0.7f;
		tex->potHeight *= 0.7f;
		img->addObject(tex);
		freeImage(tex);
	}
	img->position = iPointMake(0, 0);
	img->_aniDt = 0.01f;
	img->_repeatNum = 1;

	_ehEffectHit[1] = (EffectHit*)malloc(sizeof(EffectHit) * _ehNum);
	for (i = 0; i < _ehNum; i++)
		_ehEffectHit[1][i].img = img->copy();


	ehEffectHit = (EffectHit**)malloc(sizeof(EffectHit*) * 2 * _ehNum);
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


#include "Player.h"
extern Player* hero;
extern Object** goblins;
extern Object** mushrooms;
extern Object** ghostwarriors;
extern int goblinNum;
extern int mushNum;

extern Object** orcs;

struct Projectile
{
	iImage* img;
	iPoint p;
	int dir;
	int speed;
	int index;
	//int targetNum;
	iSize rectSize = iSizeMake(32, 32);
	//Object** target;
	int shooter; // 0 : player , 1: enermy;
	float damage;

	bool paint(float dt, iPoint off)
	{

		if (dir == 1)
			p += iPointMake(1, 0) * speed;

		else if (dir == 2)
			p += iPointMake(0, -1) * speed;
		else if (dir == 3)
			p += iPointMake(0, 1) * speed;

		else
			p += iPointMake(-1, 0) * speed;
		
		img->paint(dt, p + off);
		img->leftRight = 0;

		/*
		extern int gameState;

		
			for (int i = 0; i < targetNum; i++)
			{

				if (gameState == 1)
				{
					if (containPoint(iPointMake(p.x, p.y + 32), iRectMake(target[i]->position.x, target[i]->position.y, 64, 64)))
					{

						if (((Monster*)target[i])->type == 2)
						{
							((Goblin*)target[i])->setDmg(7);
							addEffectHit(0, target[i]->position);
							//zoomCamera(target[i]->position, 1.5);
							return true;
						}

					}
				}
			}
		*/
		if (shooter == 0) // 발사한 오브젝트가 player 일때
		{
			if (goblinNum > 0) // 고블린이 살아 있으면
			{
				for (int j = 0; j < goblin_Num; j++)
				{


					if (containPoint(p, iRectMake(goblins[j]->position.x - 16, goblins[j]->position.y - 16, 32, 32)))
					{
						// 데미지 주는곳
						goblins[j]->setDamage(7);
						addNumber(7, goblins[j]->position);
						goblins[j]->setBehave(ObjectBehave::ObjectBehave_hurt, goblins[j]->direction);
						//projectile[i]->
						addEffectHit(0,p);

						return true;
					}

				}
			}

			if (mushNum > 0) // 버섯이 살아있으면
			{
				for (int j = 0; j < mush_Num; j++)
				{
					//printf("projectile %f %f\n", projectile[i]->p.x, projectile[i]->p.y);
					//printf("mush %f %f\n", mushrooms[j]->position.x, mushrooms[j]->position.y);

					if (containPoint(p, iRectMake(mushrooms[j]->position.x - 55, mushrooms[j]->position.y - 35, 110, 70)))
					{
						mushrooms[j]->setDamage(7);
						addNumber(7, mushrooms[j]->position);
						mushrooms[j]->setBehave(ObjectBehave::ObjectBehave_hurt, mushrooms[j]->direction);
						addEffectHit(0, p);

						return true;

					}

				}
			}

			for(int j = 0; j<1; j++)
			{
				if(containPoint(p, iRectMake(ghostwarriors[j]->position.x, ghostwarriors[j]->position.y,100, 500)))
				{
					ghostwarriors[j]->setDamage(7);
					addNumber(7, ghostwarriors[j]->position);
					ghostwarriors[j]->setBehave(ObjectBehave::ObjectBehave_hurt, ghostwarriors[j]->direction);
					addEffectHit(0, p);

					return true;
				}
			}
		}
		else if (shooter == 1) // 발사한 오브젝트가 enermy 일때
		{
			if (containRect(img->touchRect(), hero->img->touchRect())) // 적이 쏜 투사체와 플레이어가 충돌하였을때
			{
				printf("player hit!\n");

				return true;
			}
		}
		else if(shooter ==2 && index == 2 && img->frame == 1) // 발사한 오브젝트가 boss고 지진스킬 애니메이션이 시작할때 한번만 체크
		{
			
				if(hero->getPosition().y == 631.0f) // 플레이어가 점프하지 않으면 데미지 입음.
				{
					hero->setDamage(7);
					addEffectHit(0, hero->position);
					addNumber(7, hero->position);


					//return true;
				}
		
		}
		else if (shooter == 2 )  // 발사한 오브젝트가 boss면
		{
			if (containPoint(p, iRectMake(hero->getPosition().x, hero->getPosition().y, 100, 100))) // 플레이어와 충돌시
			{
				printf("meteor hit@@@@@@@@@@@@@@@@@@@@@@@@@@@@@!!!!@@@@@@@@@@@@@@@@!\n");
		
				hero->setDamage(15.0);
				addEffectHit(1, iPointMake(p.x-200, p.y-200));
				addNumber(15, hero->position);
				
				return true;
			}
			else if (gameState == gs_villege)
			{
				if (containPoint(p, iRectMake(0,800,100,000))) // 땅에 충돌시
				{
					printf("explosion\n");
					addEffectHit(1, iPointMake(p.x-200, p.y-200));
					return true;
				}
			}
		}



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
	_projectile = (Projectile**)malloc(sizeof(Projectile*) * 4); // 0 : 플레이어 2 번스킬 , 1 : Mushroom 투사체 2 : boss Skill1 바닥이펙트
	// 4 :보스 메테오
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

	img = new iImage();
	for (int i = 0; i < 22; i++)
	{
		Texture* tex = createImage("assets/stage/mushroom/Skill1/Projectile (%d).png", i + 1);
		img->addObject(tex);
		freeImage(tex);
	}

	img->position = iPointMake(-188, -188);
	img->_aniDt = 0.03f;
	img->_repeatNum = 1;

	_projectile[1] = (Projectile*)malloc(sizeof(Projectile) * _projectNum);

	for (i = 0; i < _projectNum; i++)
		_projectile[1][i].img = img->copy();

	delete img;

	img = new iImage();
	for (int i = 0; i < 25; i++)
	{
		Texture* tex = createImage("assets/stage/ghostwarrior/Skill1/skill (%d).png", i+1);
		img->addObject(tex);
		freeImage(tex);
	}

	img->position = iPointMake(0, 0);
	img->aniDt = 0.0f;
	img->_aniDt = 0.025f;
	img->_repeatNum = 1;


	_projectile[2] = (Projectile*)malloc(sizeof(Projectile) * _projectNum);

	for (i = 0; i < _projectNum; i++)
		_projectile[2][i].img = img->copy();



	delete img;

	img = new iImage();
	for (int i = 0; i < 61; i++)
	{
		Texture* tex = createImage("assets/stage/props/fire/tile%03d.png", i);

		tex->height *= 3.0f;
		tex->width *= 3.0f;
		tex->potHeight *= 3.0f;
		tex->potWidth *= 3.0f;
		
		img->addObject(tex);
		img->leftRight = 1;
	
		freeImage(tex);
	}

	img->position = iPointMake(0, 0);
	img->aniDt = 0.0f;
	img->_aniDt = 0.025f;
	img->_repeatNum = 0;

	_projectile[3] = (Projectile*)malloc(sizeof(Projectile) * _projectNum);

	for (i = 0; i < _projectNum; i++)
		_projectile[3][i].img = img->copy();

	projectile = (Projectile**)malloc(sizeof(Projectile*) * 4 * _projectNum);
	projectNum = 0;
}

void freeProjectile()
{
	for (int j = 0; j < 2; j++)
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
		//printf("%f ,%f shot \n", projectile[i]->p.x, projectile[i]->p.y);
		if (projectile[i]->paint(dt, off))
		{
			projectNum--;
			for (int j = i; j < projectNum; j++)
				projectile[j] = projectile[1 + j];
		}

	}
}

void addProjectile(int index, iPoint p, int direction, int speed, int shooter)// Object** ObjTarget, int TargetNum)
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
			pj->index = index;
			//pj->target = ObjTarget;
			//pj->targetNum = TargetNum;
			pj->shooter = shooter;

			projectile[projectNum] = pj;
			projectNum++;
			return;
		}

	}
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

