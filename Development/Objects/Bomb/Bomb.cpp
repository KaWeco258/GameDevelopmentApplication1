#include "Bomb.h"
#include "DxLib.h"
#include "../Enemy/BoxEnemy.h"

//コンストラクタ
Bomb::Bomb() : animation_count(0), direction(0.0f),box_size(0.0),radian(0.0), bomb_image(0)
{
	bomb_animation = NULL;
}

//デストラクタ
Bomb::~Bomb()
{

}

//初期化処理
void Bomb::Initialize()
{
	//画像の読み込み
	bomb_animation = LoadGraph("Resource/Images/Bomb/Bomb.png");
	

	//エラーチェック
	if (bomb_animation == -1)
	{
		throw("爆弾の画像がありません\n");
	}
	
	

	//向きの設定
	radian = -1.6f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	bomb_image = bomb_animation;
	

	//初期進行方向の設定
	direction = Vector2D(1.0f, -0.5f);


}

//更新処理
void Bomb::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	//AnimationControl();
}

//描画処理
void Bomb::Draw() const
{
	//画像フラグ
	int flip_flag = FALSE;

	//進行方向によって、反転状態を決定する
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//情報をもとにハコテキ画像を描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, bomb_image, TRUE, flip_flag);                

	//親クラスの描画処理を呼び出す
	__super::Draw();

	//デバッグ用
#if _DEBUG
	//当たり判定の可視化
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif	   
}

//終了時処理
void Bomb::Finalize()
{
	//使用した画像を解放
	DeleteGraph(bomb_animation);
	
}



//移動処理
void Bomb::Movement()
{
	
	//一番下まで爆弾を落とす
	if (((location.y + direction.y) < box_size.y) ||
		(580.0f - box_size.y) < (location.y + direction.y))
	{
		direction.x = 0.0f;
		direction.y *= 1.1f;
	}

	//現在の位置座標に速さを加算する
	location -= direction;


	

}

//当たり判定通知処理
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
	
	//爆弾に当たって無かったら
	if (dynamic_cast<BoxEnemy*>(hit_object) != nullptr)
	{
		//敵を描画し続ける
		Efface = TRUE;
	}
	//爆弾に当たったら
	else
	{
		//敵を消す処理
		Efface = FALSE;
		
	}
}

////アニメーション制御
//void Bomb::AnimationControl()
//{
//	//アニメーションカウントを計算する
//	animation_count++;
//
//	//30フレーム目に到達したら
//	if (animation_count >= 30)
//	{
//		//カウントをリセット
//		animation_count = 0;
//
//		//画像の切り替え
//		if (boxenemy_image == boxenemy_animation[0])
//		{
//			boxenemy_image = boxenemy_animation[1];
//		}
//		else
//		{
//			boxenemy_image = boxenemy_animation[0];
//		}
//
//		if (wingenemy_image == wingenemy_animation[0])
//		{
//			wingenemy_image = wingenemy_animation[1];
//		}
//		else
//		{
//			wingenemy_image = wingenemy_animation[0];
//		}
//	}
//}