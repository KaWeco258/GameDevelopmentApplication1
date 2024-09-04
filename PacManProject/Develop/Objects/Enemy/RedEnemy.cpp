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
}

void RedEnemy::Update(float delta_second)
{
}

void RedEnemy::Draw(const Vector2D& screen_offset) const
{
}

void RedEnemy::Finalize()
{
}

void RedEnemy::Movement()
{
}

void RedEnemy::Animation()
{
}
