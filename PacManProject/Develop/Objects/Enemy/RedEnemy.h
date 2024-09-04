#pragma once

#include "EnemyBase.h"

class RedEnemy : public  EnemyBase
{
public:
	RedEnemy();
	virtual ~RedEnemy();

	 void Initialize() override;
	 void Update(float delta_second) override;
	 void Draw(const Vector2D& screen_offset) const override;
	 void Finalize() override;

	 void Movement();
	 void Animation();
};

