#include "Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Player::Player() : location(), direction(0.0f), radius(15.0f)
{
}

Player::Player(float x, float y) : location(x, y), direction(0.0f), radius(15.0f)
{
}

Player::Player(Vector2D location) : direction(0.0f), radius(15.0f)
{
	this->location = location;
}

//デストラクタ
Player::~Player()
{

}

//更新処理
void Player::Update()
{
	//移動処理
	Movement();
}

//描画処理
void Player::Draw() const
{
	//メンバ変数の値をもとに円を描画する
	DrawCircleAA(location.x, location.y, radius, 50, GetColor(255, 255, 255), TRUE);
}

//位置情報設定処理
void Player::SetLocation(float x, float y)
{
	SetLocation(Vector2D(x, y));
}
void Player::SetLocation(Vector2D location)
{
	this->location = location;
}

//位置情報取得
Vector2D Player::GetLocation() const
{
	return location;
}

//円の半径の大きさを取得
float Player::GetRadius()
{
	return radius;
}

//移動処理
void Player::Movement()
{
	//静的メンバを呼び出して、入力情報を取得する
	//上矢印キーを押したら円を上方向へ進行させる
	if (InputControl::GetKeyDown(KEY_INPUT_UP))
	{
		direction.y = -1.0f;
	}

	//下矢印キーを押したら円を下方向へ進行させる
	if (InputControl::GetKeyDown(KEY_INPUT_DOWN))
	{
		direction.y = 1.0f;
	}

	//右矢印キーを押したら円を右方向へ進行させる
	if (InputControl::GetKeyDown(KEY_INPUT_RIGHT))
	{
		direction.x = 1.0f;
	}

	//左矢印キーを押したら円を左方向へ進行させる
	if (InputControl::GetKeyDown(KEY_INPUT_LEFT))
	{
		direction.x = -1.0f;
	}

	//位置座標を進行方向に代入する
	location += direction;
}