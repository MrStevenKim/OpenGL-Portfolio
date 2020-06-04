#pragma once
#include "Playerable.h"



class Player : public Playerable
{
public:
	Player();
	virtual ~Player();

	static void cbBehave(void* cb);
	static void cbSkill1(void* cb);
	static void cbSkill2(void* cb);
	static void cbSkill3(void* cb);
	void setBehave(ObjectBehave be, int direction);
	void paint(float dt, iPoint offset);

	//override func
	bool moveForMouse(float dt, int NumX, int NumY);
	
public:
	iImage* imgSkill; // 근접 스킬
	iImage* imgSKillHit; // 타격시 이펙트
	iImage* imgRange; // 원거리 스킬
	iImage* imgBuff; // 버프 스킬
	iImage* Ultimate; // 궁극기

	void Skill1();
	void Skill2();
	void Skill3();

	float CoolDown_SK1;
	float _CoolDown_SK1; // 쿨다운 최대치
	float CoolDown_SK2;
	float _CoolDown_SK2; // 쿨다운 최대치
	float CoolDown_SK3;
	float _CoolDown_SK3; // 쿨다운 최대치

public:



};

extern Player* hero;

