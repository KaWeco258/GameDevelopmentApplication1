#include "BombBlast.h"
#include "DxLib.h"
#include "../BoxEnemy/BoxEnemy.h"
#include "../Bomb/Bomb.h"

//コンストラクタ
BombBlast::BombBlast() : animation_count(0), direction(0.0f),box_size(0.0),radian(0.0), blast_image(0)
{
	blast_animation[0] = NULL;
	blast_animation[1] = NULL;
	blast_animation[2] = NULL;
}

//デストラクタ
BombBlast::~BombBlast()
{

}

//初期化処理
void BombBlast::Initialize()
{
	//画像の読み込み
	//bomb_animation = LoadGraph("Resource/Images/Bomb/Bomb.png");
	blast_animation[0] = LoadGraph("Resource/Images/Blast/1.png");
	blast_animation[1] = LoadGraph("Resource/Images/Blast/2.png");
	blast_animation[2] = LoadGraph("Resource/Images/Blast/3.png");
	

	//エラーチェック
	/*if (bomb_animation == -1)
	{
		throw("爆弾の画像がありません\n");
	}*/

	if (blast_animation[0] == -1 || blast_animation[1] == -1 || blast_animation[2] == -1)
	{
		throw("爆風の画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	//bomb_image = bomb_animation;
	blast_image = blast_animation[0];
	

	//初期進行方向の設定
	direction = Vector2D(1.0f, -0.5f);


}

//更新処理
void BombBlast::Update()
{
	//移動処理
	//Movement();
	//アニメーション制御
	AnimationControl();
}

//描画処理
void BombBlast::Draw() const
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

	//情報をもとに爆弾画像を描画
	//DrawRotaGraphF(location.x, location.y, 0.8, radian, bomb_image, TRUE, flip_flag);                
	DrawRotaGraphF(location.x, location.y, 0.8, radian, blast_image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	//__super::Draw();

	//デバッグ用
//#if _DEBUG
//	//当たり判定の可視化
//	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
//	Vector2D box_collision_lower_right = location + (box_size / 2.0f);
//
//	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
//		box_collision_lower_right.x, box_collision_lower_right.y,
//		GetColor(255, 0, 0), FALSE);
//#endif	   
}

//終了時処理
void BombBlast::Finalize()
{
	//使用した画像を解放
	//DeleteGraph(bomb_animation);
	DeleteGraph(blast_animation[0]);
	DeleteGraph(blast_animation[1]);
	DeleteGraph(blast_animation[2]);
}



//移動処理
//void BombBlast::Movement()
//{
//	
//	//一番下まで爆弾を落とす
//	if (((location.y + direction.y) < box_size.y) ||
//		(580.0f - box_size.y) < (location.y + direction.y))
//	{
//		direction.x = 0.0f;
//		direction.y *= 1.1f;
//	}
//
//	//現在の位置座標に速さを加算する
//	location -= direction;
//
//
//	
//
//}
//

//当たり判定通知処理
void BombBlast::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
	
	//爆弾に当たって無かったら
	//if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	//{
	//	//敵を描画し続ける
	//	Efface = TRUE;
	//}
	////爆弾に当たったら
	//else
	//{
	//	//敵を消す処理
	//	Efface = FALSE;
	//	//アニメーション制御
	//	
	//}
	//AnimationControl();
}

//アニメーション制御
void BombBlast::AnimationControl()
{
	//アニメーションカウントを計算する
	animation_count++;
	
	

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントをリセット
		animation_count = 0;

		/*if(Efface==FALSE)
		{*/
			//NULLだったのをアニメーションに変換させる
		//	blast_image = blast_animation[0];
			
			//画像の切り替え
			if (blast_image == blast_animation[0])
			{
				blast_image = blast_animation[1];
			}
			else if (blast_image == blast_animation[1])
			{
				blast_image = blast_animation[2];
			}
			else if (blast_image == blast_animation[2])
			{
				blast_image = NULL;
			}
			
		/*}*/
	}
}