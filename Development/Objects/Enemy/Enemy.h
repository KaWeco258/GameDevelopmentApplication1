#pragma once

#include "../../Utility/Vector2D.h"

//ゲームオブジェクト基底クラス
class Enemy
{
protected:
	Vector2D location;     //位置情報
	double scale;          //大きさ
	double radian;         //向き
	int image;             //描画する画像
	int sound;             //再生する音源

private:
	int animation[2];      //アニメーション画像
	int animation_count;   //アニメーション時間
	int flip_flag;         //反転フラグ


public:
	Enemy();                  //コンストラクタ
	virtual ~Enemy();         //デストラクタ

	virtual void Initialize();     //初期化処理
	virtual void Update();         //更新処理
	virtual void Draw() const;     //描画処理
	virtual void Finalize();       //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(Enemy* hit_object);

	

private:
	//アニメーション制御
	void AnimationControl();

};