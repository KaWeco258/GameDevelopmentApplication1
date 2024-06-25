#include "GoldEnemy.h"
#include "DxLib.h"
#include "../Bomb/Bomb.h"

//コンストラクタ
GoldEnemy::GoldEnemy() : animation_count(0), direction(0.0f)
{
	goldenemy_animation[0] = NULL;
	goldenemy_animation[1] = NULL;
	goldenemy_animation[2] = NULL;
	goldenemy_animation[3] = NULL;
	goldenemy_animation[4] = NULL;


}

//デストラクタ
GoldEnemy::~GoldEnemy()
{

}

//初期化処理
void GoldEnemy::Initialize()
{
	//画像の読み込み
	goldenemy_animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	goldenemy_animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	goldenemy_animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	goldenemy_animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	goldenemy_animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
	

	//エラーチェック
	if (goldenemy_animation[0] == -1 || goldenemy_animation[1] == -1 || goldenemy_animation[2] == -1 || goldenemy_animation[3] == -1 || goldenemy_animation[4] == -1)
	{
		throw("ゴールドテキの画像がありません\n");
	}
	
	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	goldenemy_image = goldenemy_animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);


}

//更新処理
void GoldEnemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();
}

//描画処理
void GoldEnemy::Draw() const
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

	//情報をもとにキンテキ画像を描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, goldenemy_image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void GoldEnemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(goldenemy_animation[0]);
	DeleteGraph(goldenemy_animation[1]);
	DeleteGraph(goldenemy_animation[2]);
	DeleteGraph(goldenemy_animation[3]);
	DeleteGraph(goldenemy_animation[4]);
	
}


//移動処理
void GoldEnemy::Movement()
{
	//画面端に到達したら、進行方向を反転させる
	/*if (((location.x + direction.x) < box_size.x) ||
		(940.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(580.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}*/

	//進行方向に向かって、位置座標を変更する
	location += direction;
}

//当たり判定通知処理
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
	//direction = 0.0f;

	//爆弾に当たって無かったら
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
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


//アニメーション制御
void GoldEnemy::AnimationControl()
{
	//アニメーションカウントを計算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントをリセット
		animation_count = 0;

		//画像の切り替え
		if (goldenemy_image == goldenemy_animation[0])
		{
			goldenemy_image = goldenemy_animation[1];
		}
		else if (goldenemy_image == goldenemy_animation[1])
		{
			goldenemy_image = goldenemy_animation[2];
		}
		else if (goldenemy_image == goldenemy_animation[2])
		{
			goldenemy_image = goldenemy_animation[3];
		}
		else if (goldenemy_image == goldenemy_animation[3])
		{
			boxenemy_image = goldenemy_animation[4];
		}
		else if (goldenemy_image == goldenemy_animation[4])
		{
			goldenemy_image == goldenemy_animation[0];
		}

		
	}
}