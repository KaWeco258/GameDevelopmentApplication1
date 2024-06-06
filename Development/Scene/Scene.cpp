#include "Scene.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Player/Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Objects/Bomb/Bomb.h"

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects(),bg(0),ti(0)
{
	number[0] = NULL;
	number[1] = NULL;
	number[2] = NULL;
	number[3] = NULL;
	number[4] = NULL;
	number[5] = NULL;
	number[6] = NULL;
	number[7] = NULL;
	number[8] = NULL;
	number[9] = NULL;
}

//デストラクタ
Scene::~Scene()
{
	//忘れ防止
	Finalize();
}

//初期化処理
void Scene::Initialize()
{
	bg = LoadGraph("Resource/Images/BackGround.png");
	ti = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
	number[0] = LoadGraph("Resource/Images/Score/0.png");
	number[1] = LoadGraph("Resource/Images/Score/1.png");
	number[2] = LoadGraph("Resource/Images/Score/2.png");
	number[3] = LoadGraph("Resource/Images/Score/3.png");
	number[4] = LoadGraph("Resource/Images/Score/4.png");
	number[5] = LoadGraph("Resource/Images/Score/5.png");
	number[6] = LoadGraph("Resource/Images/Score/6.png");
	number[7] = LoadGraph("Resource/Images/Score/7.png");
	number[8] = LoadGraph("Resource/Images/Score/8.png");
	number[9] = LoadGraph("Resource/Images/Score/9.png");
	

	//プレイヤーを生成する
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
}

//更新処理
void Scene::Update()
{
	//オブジェクトリスト内のオブジェクトを更新
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//オブジェクト同士の当たり判定チェック
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//当たり判定チェック処理
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Zキーを押したら、敵を生成
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 520.0f));
	}

	//スペースキーを押したら、爆弾を生成
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<Player*>(objects[i]) != nullptr)
			{
				CreateObject<Bomb>(objects[i]->GetLocation());
			}
		}
		
	}

	
}

//描画処理
void Scene::Draw() const
{
	DrawExtendGraph(0.0, 0.0, 940.0, 640.0, bg, FALSE);
	DrawBoxAA(0.0, 580.0, 941.0, 650.0, GetColor(0, 0, 0), TRUE);
	DrawGraph(40.0, 588.0, ti, FALSE);


	//オブジェクトリスト内のオブジェクトを描画
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//終了時処理
void Scene::Finalize()
{
	//動的配列が空なら処理を終了する
	if (objects.empty())
	{
		return;
	}

	//各オブジェクトを削除する
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//動的配列の解放
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//当たり判定チェック処理(矩形の中心で当たり判定をとる)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2つのオブジェクトの距離を取得
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2つのオブジェクトの当たり判定の大きさを取得
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//距離より大きさが大きい場合、Hit判定とする
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//当たったことをオブジェクトに通知
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else

//当たり判定チェック処理(左上頂点の座標から当たり判定計算を行う)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//右下頂点座標を取得する
	Vector2D a_lower_right = a->Getlocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->Getlocation() + b->GetBoxSize();

	//矩形Aと矩形Bの位置関係を調べる
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//オブジェクトに対してHIT判定を通知
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER
