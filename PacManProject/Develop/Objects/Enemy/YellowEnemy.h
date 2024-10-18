#pragma once

#include "EnemyBase.h"

class YellowEnemy : public  EnemyBase
{
public:

	const int animation_yellow[2] = { 6, 7 };
public:
	YellowEnemy();
	virtual ~YellowEnemy();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	void Movement(float delta_second);
	void Animation(float delta_second);
};

