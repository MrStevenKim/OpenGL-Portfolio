#pragma once
#include "Object.h"


enum EnermyBehave
{
	EnermyBehave_idle = 0,
	EnermyBehave_meleeAttack,
	EnermyBehave_move,
	EnermyBehave_jumpAndFall,
	EnermyBehave_hurt,
	EnermyBehave_death,

	EnermyBehave_num,
};


class Monster : public Object // 모든 몬스터(ex, 오크, 아처 들은 이 부모클래스를 상속받음)
{
public: Monster();
	  virtual ~Monster();


public:
	EnermyBehave behave;
	float roamingDt;
	float _roamingDt = 2.0f;
	
	bool detected_Player;
	iPoint Target_Pos;
	Object* Target;

	float aiTime = 0.0f;
	float _aiTime;

	float rateV;
	iPoint v = iPointZero;
	int direction;
	bool alive;

	float r = 0.0f;
	float rValue = 1.0f; // 임시로 public...

public:


	//setter;
	void setDetected_Player(bool check);
	void setTarget(Object* obj);

	//getter;
	bool getDetected_Player();
	Object* getTarget();


	static void cbBehave(iImage* img);
	static void cbSkill(iImage* skillimg);

	virtual void setBehave(EnermyBehave be, int direction) = 0;
	virtual void paint(float dt, iPoint offset) = 0;

	iImage** imgs;
	iImage* img;

	void Skill1();
	void Skill2();
};



