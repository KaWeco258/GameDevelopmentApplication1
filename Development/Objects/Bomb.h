#pragma once

#include "../Utility/Vector2D.h"


//ゲームオブジェクト基底クラス
class Bomb

{
private:
	int animation_count;   //アニメーション時間
	Vector2D direction;     //進行方向
	int bomb_animation;             //描画する画像
	double radian;         //向き
	Vector2D location;     //位置情報
	Vector2D box_size;          //大きさ
	int bomb_image;             //描画する画像


public:
	Bomb();                  //コンストラクタ
	~Bomb();                 //デストラクタ

	virtual void Initialize();     //初期化処理
	virtual void Update();         //更新処理
	virtual void Draw() const;     //描画処理
	virtual void Finalize();       //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(Bomb* hit_object);



private:
	//移動処理
	void Movement();
	//アニメーション制御
	//void AnimationControl();

	
};