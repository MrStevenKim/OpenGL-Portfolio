#pragma once

#include "CanNotMove.h"
#include "stageTileInfo.h"
#include "Player.h"
#include "coin.h"
enum CoinStat
{
	CoinStat_wait = 0,
	CoinStat_move,
	CoinStat_disappear
};

class Coin : public CanNotMove
{
public:
	Coin();
	virtual ~Coin();

public:
	void paint(float dt, iPoint offset, MapTile* tile, int NumX, int NumY);

	void set(iPoint p, int price);
	bool touchRect(iPoint p);

	CoinStat stat;
	iPoint sp, tp;
	float delta;
	int price;
};

#define coin_wait_delta 1.0f
#define coin_move_delta 1.2f
#define coin_disappear_delta 0.5f