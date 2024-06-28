#include "Harpy.h"
#include "DxLib.h"
#include "../Bomb/Bomb.h"

//コンストラクタ
Harpy::Harpy() : animation_count(0), direction(0.0f)
{
	harpy_animation[0] = NULL;
	harpy_animation[1] = NULL;


}

//デストラクタ
Harpy::~Harpy()
{

}

//初期化処理
void Harpy::Initialize()
{
	//画像の読み込み
	harpy_animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
	harpy_animation[1] = LoadGraph("Resource/Images/Harpy/2.png");
	

	//エラーチェック
	if (harpy_animation[0] == -1 || harpy_animation[1] == -1)
	{
		throw("ハーピーの画像がありません\n");
	}
	
	//0，1で数字を取得
	//int r = GetRand(1);

	//箱敵のスピードをランダムに設定する
	speed = 0.0f;

	////rが0なら左から出現、1なら右から出現
	//if (r == 0)
	//{
	//	//右
	//	direction = Vector2D(speed, 0.0f);
	//	this->location.x = 80.0f;
	//}
	//else
	//{
	//	//左
	//	direction = Vector2D(-speed, 0.0f);
	//	this->location.x = 800.0f;
	//}


	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	box_size = 64.0f;

	//初期画像の設定
	boxenemy_image = harpy_animation[0];

	//初期進行方向の設定
	direction = Vector2D(1.0f, 0.0f);


}

//更新処理
void Harpy::Update()
{
	//移動処理
	Movement();
	//アニメーション制御
	AnimationControl();
}

//描画処理
void Harpy::Draw() const
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

	//情報をもとにハーピー画像を描画
	DrawRotaGraphF(location.x, location.y, 0.8, radian, harpy_image, TRUE, flip_flag);

	//親クラスの描画処理を呼び出す
	__super::Draw();
}

//終了時処理
void Harpy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(harpy_animation[0]);
	DeleteGraph(harpy_animation[1]);
	
}


//移動処理
void Harpy::Movement()
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

//移動方向の設定
Vector2D Harpy::SetDirection(Vector2D& E_direction)
{
	return this->direction.x = E_direction.x;
}

//当たり判定通知処理
void Harpy::OnHitCollision(GameObject* hit_object)
{
	//当たった時に行う処理
	//direction = 0.0f;

	//爆弾に当たって無かったら
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		score = -50;
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
void Harpy::AnimationControl()
{
	//アニメーションカウントを計算する
	animation_count++;

	//30フレーム目に到達したら
	if (animation_count >= 30)
	{
		//カウントをリセット
		animation_count = 0;

		//画像の切り替え
		if (harpy_image == harpy_animation[0])
		{
			harpy_image = harpy_animation[1];
		}
		else
		{
			harpy_image = harpy_animation[0];
		}

		
		
	}
}