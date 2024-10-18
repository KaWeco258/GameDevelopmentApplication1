#include "EnemyBase.h"
#include "../../Utility/InputManager.h"
#include "../../Utility/ResourceManager.h"
#include "DxLib.h"
#include "../Food/Food.h"
#include "../Player/Player.h"

#define D_PLAYER_SPEED	(50.0f)

EnemyBase::EnemyBase() :
	move_animation(),
	eyes_animation(),
	velocity(0.0f),
	enemy_state(eEnemyState::ENEMY_MOVE),
	now_direction_state(eDirectionState::ENEMY_LEFT),
	next_direction_state(eDirectionState::ENEMY_LEFT),
	//food_count(0),
	animation_time(0.0f),
	ijike_time(0.0f),
	animation_count(0),
	old_panel(ePanelID::NONE),
	eye_image(NULL),
	is_ijike(false),
	//is_power_up(false),
	powerdown(false)
	//is_destroy(false)
{

}

EnemyBase::~EnemyBase()
{

}

void EnemyBase::Initialize()
{
	// アニメーション画像の読み込み
	ResourceManager* rm = ResourceManager::GetInstance();
	eyes_animation = rm->GetImages("Resource/Images/eyes.png", 4, 4, 1, 32, 32);
	eye_image = eyes_animation[1];

	// 当たり判定の設定
	collision.is_blocking = true;
	collision.object_type = eObjectType::enemy;
	collision.hit_object_type.push_back(eObjectType::player);
	collision.hit_object_type.push_back(eObjectType::wall);
	
	collision.radius = (D_OBJECT_SIZE - 1.0f) / 2.0f;

	// レイヤーの設定
	z_layer = 5;

	// 可動性の設定
	mobility = eMobilityType::Movable;

	velocity = Vector2D(2.0f, 0.0f);

	//いじける時間
	ijike_time = 8.0f;
}

void EnemyBase::Update(float delta_second)
{
	// プレイヤー状態によって、動作を変える
	switch (enemy_state)
	{
	case eEnemyState::ENEMY_IJIKE:
		Movement(delta_second);
		// 移動中のアニメーション
		animation_time += delta_second;
		if (animation_time >= (1.0f / 16.0f))
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 2)
			{
				animation_count = 0;
			}
			
		}
		break;

	case eEnemyState::ENEMY_MOVE:
		// 移動処理
		Movement(delta_second);
		// アニメーション制御
		AnimationControl(delta_second);
		break;

	case eEnemyState::ENEMY_HOME:
		Movement(delta_second);
		AnimationControl(delta_second);
		break;
	default:
		break;
	}

	if (is_ijike == true)
	{
		enemy_state = eEnemyState::ENEMY_IJIKE;
		ijike_time -= delta_second;
		if (ijike_time <= 0)
		{
			enemy_state = eEnemyState::ENEMY_MOVE;
			is_ijike = false;
			powerdown = true;
		}
	}
	else
	{
		powerdown = false;
		ijike_time = 8.0f;
	}

	
}

void EnemyBase::Draw(const Vector2D& screen_offset) const
{
	//// 親クラスの描画処理を呼び出す
	//__super::Draw(screen_offset);
	Vector2D graph_location = this->location + screen_offset;
	// オフセット値を基に画像の描画を行う
	if (enemy_state == eEnemyState::ENEMY_MOVE || enemy_state == eEnemyState::ENEMY_IJIKE)
	{
		// オフセット値を基に画像の描画を行う
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, red_image, TRUE);
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, blue_image, TRUE);
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, yellow_image, TRUE);
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, pink_image, TRUE);
	}
	
	if (enemy_state == eEnemyState::ENEMY_MOVE || enemy_state == eEnemyState::ENEMY_HOME)
	{
		DrawRotaGraphF(graph_location.x, graph_location.y, 1.0, 0.0, eye_image, TRUE);
	}
	

	

}

void EnemyBase::Finalize()
{
	// 動的配列の解放
	move_animation.clear();
	eyes_animation.clear();
}

/// <summary>
/// 当たり判定通知処理
/// </summary>
/// <param name="hit_object">当たったゲームオブジェクトのポインタ</param>
void EnemyBase::OnHitCollision(GameObjectBase* hit_object)
{
	// 当たった、オブジェクトが壁だったら
	if (hit_object->GetCollision().object_type == eObjectType::wall)
	{
		// 当たり判定情報を取得して、カプセルがある位置を求める
		CapsuleCollision hc = hit_object->GetCollision();
		hc.point[0] += hit_object->GetLocation();
		hc.point[1] += hit_object->GetLocation();

		// 最近傍点を求める
		Vector2D near_point = NearPointCheck(hc, this->location);

		// Playerからnear_pointへの方向ベクトルを取得
		Vector2D dv2 = near_point - this->location;
		Vector2D dv = this->location - near_point;

		// めり込んだ差分
		float diff = (this->GetCollision().radius + hc.radius) - dv.Length();

		// diffの分だけ戻る
		location += dv.Normalize() * diff;

		//
		velocity *= -1;
	}

	//// 当たった、オブジェクトが通常餌だったら
	if (hit_object->GetCollision().object_type == eObjectType::player&&enemy_state==eEnemyState::ENEMY_IJIKE)
	{
		is_ijike = false;
		enemy_state = eEnemyState::ENEMY_HOME;
	}


}

//eEnemyState EnemyBase::GetEnemyState() const
//{
//	return eEnemyState();
//}




void EnemyBase::SetEnemyState()
{
	this->is_ijike = true;

}

bool EnemyBase::SetPowerDown()
{
	return powerdown;
}

/// <summary>
/// 移動処理
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::Movement(float delta_second)
{
	//// 移動量から移動方向を更新
	//if (Vector2D::Distance(old_location, location) == 0.0f)
	//{
	//	// 移動がなければ direction_state を変更する
	//	velocity = 0.0f;
	//	now_direction_state = next_direction_state;
	//	next_direction_state = eDirectionState::ENEMY_RIGHT;
	//}
	//else
	//{
	//	// 移動方向に移動していなければ direction_state を変更する
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::ENEMY_UP:
	//	case eDirectionState::ENEMY_DOWN:
	//	{
	//		float diff = location.y - old_location.y;
	//		if (((now_direction_state == eDirectionState::ENEMY_UP) && (diff < 0.0f)) ||
	//			((now_direction_state == eDirectionState::ENEMY_DOWN) && (0.0f < diff)))
	//		{
	//			// 移動方向に移動してるので break
	//			break;
	//		}

	//		velocity.y = 0.0f;
	//		now_direction_state = next_direction_state;
	//		//next_direction_state = eDirectionState::NONE;
	//	}
	//	break;

	//	case eDirectionState::ENEMY_LEFT:
	//	case eDirectionState::ENEMY_RIGHT:
	//	{

	//		float diff = location.x - old_location.x;
	//		if (((now_direction_state == eDirectionState::ENEMY_LEFT) && (diff < 0.0f)) ||
	//			((now_direction_state == eDirectionState::ENEMY_RIGHT) && (0.0f < diff)))
	//		{
	//			// 移動方向に移動してるので break
	//			break;
	//		}

	//		velocity.x = 0.0f;
	//		now_direction_state = next_direction_state;
	//		//next_direction_state = eDirectionState::NONE;
	//	}
	//	break;

	//	default:// 何もしない
	//		break;
	//	}
	//}

	//// 入力状態の取得
	//InputManager* input = InputManager::GetInstance();

	//// 現在パネルの状態を確認
	//ePanelID panel = StageData::GetPanelData(location);

	// //入力から移動方向を設定
	///*if (input->GetKeyDown(KEY_INPUT_UP) || input->GetButtonDown(XINPUT_BUTTON_DPAD_UP))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::UP:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::DOWN:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::UP;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::UP;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_DOWN) || input->GetButtonDown(XINPUT_BUTTON_DPAD_DOWN))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::DOWN:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::UP:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::DOWN;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::DOWN;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_LEFT) || input->GetButtonDown(XINPUT_BUTTON_DPAD_LEFT))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::LEFT:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::RIGHT:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::LEFT;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::LEFT;
	//	}
	//}
	//else if (input->GetKeyDown(KEY_INPUT_RIGHT) || input->GetButtonDown(XINPUT_BUTTON_DPAD_RIGHT))
	//{
	//	switch (now_direction_state)
	//	{
	//	case eDirectionState::RIGHT:
	//		old_panel = ePanelID::NONE;
	//	case eDirectionState::LEFT:
	//	case eDirectionState::NONE:
	//		now_direction_state = eDirectionState::RIGHT;
	//		break;

	//	default:
	//		next_direction_state = eDirectionState::RIGHT;
	//	}
	//}*/

	// //進行方向の移動量を追加
	//switch (now_direction_state)
	//{
	//case EnemyBase::ENEMY_UP:
	//	velocity.y = -2.0f;
	//	break;
	//case EnemyBase::ENEMY_DOWN:
	//	velocity.y = 2.0f;
	//	break;
	//case EnemyBase::ENEMY_LEFT:
	//	velocity.x = -2.0f;
	//	break;
	//case EnemyBase::ENEMY_RIGHT:
	//	velocity.x = 2.0f;
	//	break;
	//default:
	//	velocity = 0.0f;
	//	now_direction_state = next_direction_state;
	//	//next_direction_state = Enemy::NONE;
	//	break;
	//}

	//// 先行入力の移動量を追加
	//if ((panel != ePanelID::NONE)
	//	&& (old_panel != panel))
	//{
	//	switch (next_direction_state)
	//	{
	//	case EnemyBase::ENEMY_UP:
	//		velocity.y = -2.0f;
	//		break;
	//	case EnemyBase::ENEMY_RIGHT:
	//		velocity.x = 2.0f;
	//		break;
	//	case EnemyBase::ENEMY_DOWN:
	//		velocity.y = 2.0f;
	//		break;
	//	case EnemyBase::ENEMY_LEFT:
	//		velocity.x = -2.0f;
	//		break;
	//	default:
	//		break;
	//	}
	//}

	// //前回座標の更新
	//old_location = location;

	//// 前回パネルの更新
	//old_panel = panel;

	 //移動量 * 速さ * 時間 で移動先を決定する
	location += velocity * D_PLAYER_SPEED * delta_second;

	// //画面外に行ったら、反対側にワープさせる
	//if (location.x < 0.0f)
	//{
	//	old_location.x = 672.0f;
	//	location.x = 672.0f - collision.radius;
	//	velocity.y = 0.0f;
	//}
	//if (672.0f < location.x)
	//{
	//	old_location.x = 0.0f;
	//	location.x = collision.radius;
	//	velocity.y = 0.0f;
	//}
}

/// <summary>
/// アニメーション制御
/// </summary>
/// <param name="delta_second">1フレームあたりの時間</param>
void EnemyBase::AnimationControl(float delta_second)
{
	if (enemy_state == eEnemyState::ENEMY_MOVE)
	{
		// 移動中のアニメーション
		animation_time += delta_second;
		if (animation_time >= (1.0f / 16.0f))
		{
			animation_time = 0.0f;
			animation_count++;
			if (animation_count >= 2)
			{
				animation_count = 0;
			}
			red_image = move_animation[animation_red[animation_count]];
			blue_image = move_animation[animation_blue[animation_count]];
			yellow_image = move_animation[animation_yellow[animation_count]];
			pink_image = move_animation[animation_pink[animation_count]];
		}
	}

	if (velocity.x > 0)
	{
		eye_image = eyes_animation[1];
	}
	else if (velocity.x < 0)
	{
		eye_image = eyes_animation[3];
	}
	else if (velocity.y > 0)
	{
		eye_image = eyes_animation[2];
	}
	else if (velocity.y < 0)
	{
		eye_image = eyes_animation[0];
	}
}
