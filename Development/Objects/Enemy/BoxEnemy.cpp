#include "BoxEnemy.h"
#include "DxLib.h"
#include "../Bomb/Bomb.h"

//コンストラクタ
BoxEnemy::BoxEnemy() : animation_count(0), direction(0.0f)
{
	boxenemy_animation[0] = NULL;
	boxenemy_animation[1] = NULL;
	/*wingenemy_animation[0] = NULL;
	wingenemy_animation[1] = NULL;*/

}

//デストラクタ
BoxEnemy::~BoxEnemy()
{

}

//初期化処理
void BoxEnemy::Initialize()
{
	//画像の読み込み
	boxenemy_animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	boxenemy_animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
	/*wingenemy_animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	wingenemy_animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");*/

	//エラーチェック
	if (boxenemy_animation[0] == -1 || boxenemy_animation[1] == -1)
	{
		throw("ハコテキの画像がありません\n");
	}
	/*if (wingenemy_animation[0] == -1 || wingenemy_animation[1] == -1)
	{
		throw("ハネテキの画像がありません\n");
	}*/

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	boxenemy_image = boxenemy_animation[0];
	//wingenemy_image = wingenemy_animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);


}

//更新処理
void BoxEnemy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();
}

//描画処理
void BoxEnemy::Draw() const
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
	DrawRotaGraphF(location.x, location.y, 0.8, radian, boxenemy_image, TRUE, flip_flag);
	DrawRotaGraphF(location.x, location.y, 0.8, radian, wingenemy_image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void BoxEnemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(boxenemy_animation[0]);
	DeleteGraph(boxenemy_animation[1]);
	/*DeleteGraph(wingenemy_animation[0]);
	DeleteGraph(wingenemy_animation[1]);*/
}


//移動処理
void BoxEnemy::Movement()
{
	//画面端に到達したら、進行方向を反転させる
	if (((location.x + direction.x) < box_size.x) ||
		(940.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(580.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
   
	//進行方向に向かって、位置座標を変更する
	location += direction;
}
 
//当たり判定通知処理
void BoxEnemy::OnHitCollision(GameObject* hit_object)
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
void BoxEnemy::AnimationControl()
{
	//アニメーションカウントを計算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントをリセット
		animation_count = 0;

		//画像の切り替え
		if (boxenemy_image == boxenemy_animation[0])
		{
			boxenemy_image = boxenemy_animation[1];
		}
		else
		{
			boxenemy_image = boxenemy_animation[0];
		}

		/*if (wingenemy_image == wingenemy_animation[0])
		{
			wingenemy_image = wingenemy_animation[1];
		}
		else
		{
			wingenemy_image = wingenemy_animation[0];
		}*/
	}
}