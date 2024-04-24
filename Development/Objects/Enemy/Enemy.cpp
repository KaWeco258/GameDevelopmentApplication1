#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//コンストラクタ
Enemy::Enemy() : animation_count(0),flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

//デストラクタ
Enemy::~Enemy()
{

}

//初期化処理
void Enemy::Initialize()
{
	//画像の読み込み
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");

	//エラーチェック
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("WingEnemyの画像がありません\n");
	}

	//向きの設定
	radian = 0.0f;

	//当たり判定の大きさを設定
	scale = 64.0f;

	//初期画像の設定
	image = animation[0];

	
}

//更新処理
void Enemy::Update()
{
	location.x += 1.0f;

	//画面左で消えたらまた画面右から生成する
	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}

	//アニメーション制御
	AnimationControl();
}

//描画処理
void Enemy::Draw() const
{
	//プレイヤー画像の描画
	DrawRotaGraphF(0.0, 0.0, 1.0, radian, image, TRUE, flip_flag);
}

//終了時処理
void Enemy::Finalize()
{
	//使用した画像を解放
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//当たり判定通知処理
void Enemy::OnHitCollision(Enemy* hit_object)
{
	//当たった時に行う処理
}




//アニメーション制御
void Enemy::AnimationControl()
{
	//アニメーションカウントを計算する
	animation_count++;

	//60フレーム目に到達したら
	if (animation_count >= 60)
	{
		//カウントをリセット
		animation_count = 0;

		//画像の切り替え
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}