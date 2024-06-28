#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER  //座標の頂点を画像の中心にする

#define PLAYER	(0)
#define ENEMY	(1)
#define BOMB	(2)
#define	EFFECT	(3)


//ゲームオブジェクト基底クラス
class GameObject
{
protected:
	Vector2D location;			//位置情報
	Vector2D box_size;          //大きさ
	double radian;				//向き
	int boxenemy_image;         //描画する画像(箱敵)
	int wingenemy_image;        //描画する画像(羽敵)
	int goldenemy_image;        //描画する画像(金敵)
	int harpy_image;        //描画する画像(金敵)
	int player_image;           //描画する画像(プレイヤー)
	int sound;					//再生する音源
	bool Efface;          //消す処理(仮)
	int type;				//オブジェクトのタイプ
	int score;				//オブジェクトのタイプ

public:
	float speed;


public:
	GameObject();                  //コンストラクタ
	virtual ~GameObject();         //デストラクタ

	virtual void Initialize();     //初期化処理
	virtual void Update();         //更新処理
	virtual void Draw() const;     //描画処理
	virtual void Finalize();       //終了時処理

	//当たり判定通知処理
	virtual void OnHitCollision(GameObject* hit_object);

	//消す処理
	bool EffaceObjects();

	//オブジェクトのタイプ取得
	int GetObjectType();

	//位置情報取得処理
	Vector2D GetLocation() const;
	//
	int GetScore(); //const;
	//位置情報変更処理
	void SetLocation(const Vector2D& location);

	//当たり判定の大きさを取得する
	Vector2D GetBoxSize() const;
	
	//アニメーション制御
	void AnimationControl();
};