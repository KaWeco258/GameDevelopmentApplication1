#pragma once


#include "../GameObject.h"

//ゲームオブジェクト基底クラス
class BombBlast : public GameObject

{
private:
	int animation_count;      //アニメーション時間
	Vector2D direction;       //進行方向
	//int bomb_animation;       //描画する画像
	int blast_animation[3];       //描画する画像
	double radian;            //向き

	Vector2D box_size;        //大きさ
	//int bomb_image;           //描画する画像
	int blast_image;           //描画する画像


public:
	BombBlast();                  //コンストラクタ
	~BombBlast();                 //デストラクタ

	virtual void Initialize() override;     //初期化処理
	virtual void Update() override;         //更新処理
	virtual void Draw() const override;     //描画処理
	virtual void Finalize() override;       //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object) override;



private:
	//移動処理
	void Movement();
	
	//アニメーション制御
	void AnimationControl();

	
};