#pragma once
#include "Monster.h"

#define mush_Num 1

class Mushroom : public Monster
{
public: Mushroom(int number);
	  virtual ~Mushroom();

public:
	void paint(float dt, iPoint offset, MapTile* tile, int NumX, int NumY);

	void setBehave(ObjectBehave be, int direction);

	void Skill1();
	void setDmg(float dmg);

	static void cbDeath(void* cb);
	static void cbHurt(void* cb);
	static void cbBehave(void* cb);

public:
	void setDetected_Player(bool check);
	void setTarget(Object* obj);

	bool getDetected_Player();
	Object* getTarget();

private:
	bool detected_Player;
	iPoint Target_Pos;
	Object* Target;

public:
	int mush_number;
	iImage** imgs;
	iImage* img;

	float aiTime, _aiTime; // 반응까지에 걸리는 시간 _aiTime은 최대치
	
};