#pragma once

#include "iStd.h"
#include "stageTileInfo.h"

#define PlayerWidth 16
#define PlayerHeight 16
#define PlayerSpeed 200

#define PlayerColor 0,0,1,1



class Object
{
public: Object();
	 virtual ~Object();

public:

	Texture* tex;
	iPoint position;
	iPoint targetPosition;
	iSize size;
	iPoint jumpment;
	int jumpNum;
	int _jumpNum; // 점프를 할수 있는 최대 수
	float movement; // 이동속도를 의미함.
	float range;
	float damage;
	float speed; // 공격속도를 의미함.
	float _speed;
	float HP;
	float _HP;
	float MP;
	float _MP;
	float Stamina;
	float _Stamina;
	char name[64];

public:
	bool alive;
public: 

	//setter
	void setTex(Texture* tex);
	void setPosition(iPoint position);
	void setTargetPosition(iPoint targetPosition);
	void setSize(iSize size);
	void setMovement(float movement);
	void setRange(float range);
	void setDamage(float damage);
	void setSpeed(float speed);
	void setHP(float hp);
	void setMP(float mp);
	void setMaxHp(float _hp);
	void setMaxMp(float _mp);
	void setMaxStamina(float _stamina);
	void setStamina(float stamina);
	void setName(const char* name);

	//getter
	Texture* getTex();
	iPoint getPosition();
	iPoint getTargetPosition();
	iSize getSize();
	float getMovement();
	float getRange();
	float getDamage();
	float getSpeed();
	float getHp();
	float getMp();
	float getStamina();
	float getMaxHp();
	float getMaxMP();
	float getMaxStamina();
	const char* getName();


	

public:
	//function
	bool moveForMouse(float dt);
	void move(iPoint movement, MapTile* maptile);
	void jump();
	void applyJump(iPoint& movement, float dt);

	int path[MapTileNumX * MapTileNumY];
	int pathNum;
	int pathIndex;
};

// 한점에서 직선까지의 거리
float getDistanceLine0(iPoint p, iPoint sp, iPoint ep);
// 한점에서 선분까지의 거리
float getDistanceLine1(iPoint p, iPoint sp, iPoint ep);
