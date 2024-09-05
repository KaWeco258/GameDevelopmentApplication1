#include "RedEnemy.h"
#include "../../Utility/ResourceManager.h"


RedEnemy::RedEnemy()
{
}

RedEnemy::~RedEnemy()
{
}

void RedEnemy::Initialize()
{
	__super::Initialize();
	ResourceManager* rm = ResourceManager::GetInstance();
	move_animation = rm->GetImages("Resource/Images/monster.png", 20, 20, 1, 32, 32);
	image = move_animation[0];
}

void RedEnemy::Update(float delta_second)
{
	__super::Update(delta_second);
}

void RedEnemy::Draw(const Vector2D& screen_offset) const
{
	__super::Draw(screen_offset);
}

void RedEnemy::Finalize()
{
}

void RedEnemy::Movement(float delta_second)
{  
	__super::Movement(delta_second);
}

void RedEnemy::Animation(float delta_second)
{
	__super::AnimationControl(delta_second);

	// 移動中のアニメーション
	/*animation_time += delta_second;
	if (animation_time >= (1.0f / 16.0f))
	{
		animation_time = 0.0f;
		animation_count++;
		if (animation_count >= 2)
		{
			animation_count = 0;
		}
		image = move_animation[animation_num[animation_count]];

		

	}*/

}
