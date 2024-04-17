#pragma once

#include "../GameObject.h"

class Player
{
private:
	//位置情報
    int animation[2];
	//進行方向情報
	Vector2D direction;
	//半径
	float radius;

public:
	//コンストラクタ
	Player();
	Player(float x, float y);
	Player(Vector2D location);
	//デストラクタ
	~Player();

	//更新処理
	void Update();
	//描画処理（constメンバ関数）
	void Draw() const;

	//位置情報設定（floatでオーバーロード）
	void SetLocation(float x, float y);
	//位置情報設定（vector2Dでオーバーロード）
	void SetLocation(Vector2D location);
	//位置情報（constメンバにする）
	Vector2D GetLocation() const;
	//半径情報の取得
	float GetRadius();

private:
	//移動処理
	void Movement();
};