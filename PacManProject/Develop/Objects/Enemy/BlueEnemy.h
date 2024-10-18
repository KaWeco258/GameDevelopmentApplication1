#pragma once

#include "EnemyBase.h"

class BlueEnemy : public  EnemyBase
{
public:

	 int animation_blue[2] = { 4, 5 };
public:
	BlueEnemy();
	virtual ~BlueEnemy();

	void Initialize() override;
	void Update(float delta_second) override;
	void Draw(const Vector2D& screen_offset) const override;
	void Finalize() override;

	void Movement(float delta_second);
	void Animation(float delta_second);
};

