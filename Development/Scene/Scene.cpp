#include "Scene.h"
#include "../Objects/BoxEnemy/BoxEnemy.h"
#include "../Objects/GoldEnemy/GoldEnemy.h"
#include "../Objects/WingEnemy/WingEnemy.h"
#include "../Objects/Harpy/Harpy.h"
#include "../Objects/Player/Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Objects/Bomb/Bomb.h"
#include "../Objects/BombBlast/BombBlast.h"

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects(),bg(0),ti(0),si(0),hsi(0),GameTime(0),r(0), e_flg(FALSE)
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
	being = FALSE;
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
	//背景画像の読込み
	bg = LoadGraph("Resource/Images/BackGround.png");   
	//タイマーの画像の読込み
	ti = LoadGraph("Resource/Images/TimeLimit/timer-03.png");     
	//数字の画像の読込み
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
	//スコアという文字の画像の読込み
	si = LoadGraph("Resource/Images/Score/font-21.png");
	//ハイスコアという文字の画像の読込み
	hsi = LoadGraph("Resource/Images/Score/hs.png");
	//制限時間の初期化
	GameTime = TIMELIMIT;
	

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

	//オブジェクト同士が当たったら、それぞれオブジェクトを消す
	for (int i = 0; i < objects.size(); i++)
	{
		

		if (objects[i]->EffaceObjects()==TRUE)
		{
			
			being = FALSE;
			e_flg = FALSE;

			if (objects[i]->GetObjectType() == BOMB)
			{
				Vector2D bp;
				bp = objects[i]->GetLocation();   //爆弾の現在位置

				CreateObject<BombBlast>(bp);
			}

			objects.erase(objects.begin() + i);
			//continue;
		}
	}

	//爆弾が画面下に到達したら消す
	for (int i = 0; i < objects.size(); i++)
	{
		
		if (dynamic_cast<Bomb*>(objects[i]) != nullptr)
		{
			Vector2D bp;
			bp = objects[i]->GetLocation();   //爆弾の現在位置
			if (bp.y>532.0)
			{
				objects.erase(objects.begin() + i);
				being = FALSE;
				CreateObject<BombBlast>(bp);
			}
		}
	}

	//敵が画面左右に到達したら消す
	for (int i = 0; i < objects.size(); i++)
	{

		if (dynamic_cast<BoxEnemy*>(objects[i]) != nullptr)
		{
			Vector2D bep;
			bep = objects[i]->GetLocation();   //敵の現在位置
			if (bep.x > 900.0||bep.x < 50.0)
			{
				objects.erase(objects.begin() + i);
				e_flg = FALSE;
			}
		}
	}
	

	//画面上に爆弾が無ければ
	if (being==FALSE)
	{
		//スペースキーを押したら、爆弾を生成
		if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
		{
			for (int i = 0; i < objects.size(); i++)
			{
				if (dynamic_cast<Player*>(objects[i]) != nullptr)
				{
					CreateObject<Bomb>(objects[i]->GetLocation());
					being = TRUE;
				}
			}
		
		}
	}

	//Zキーを押したら、敵を生成
	/*if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		
	}*/
	/*while (GameTime>0)
	{*/
		

			
		
/*}*/
	//制限時間の更新
	GameTime--;
	
	/*if (GameTime == 54 || GameTime == 48 || GameTime == 42 || GameTime == 36 || GameTime == 30 || GameTime == 24 || GameTime == 18 || GameTime == 12 || GameTime == 6)
	{*/
		int GetRand(10);
		int r = GetRand % 10 + 1;
		//int SRand(r);
		if (e_flg == FALSE)
		{
			if (GameTime / 150 % 6 == 0)
			{
				CreateObject<BoxEnemy>(Vector2D(80.0f, 520.0f));
				e_flg = TRUE;
			}
		}
			//switch (GetRand % 10 + 1)
			//{
			//case 1:
			//	
			//	break;

			//case 2:
			//	if (GameTime / 150 % 6 == 0)
			//	{
			//		CreateObject<BoxEnemy>(Vector2D(200.0f, 520.0f));
			//	}
			//	break;

			//case 3:
			//	if (GameTime / 150 % 6 == 0)
			//	{
			//		CreateObject<BoxEnemy>(Vector2D(300.0f, 520.0f));
			//	}
			//	break;

			//case 4:
			//	if (GameTime / 150 % 6 == 0)
			//	{
			//		CreateObject<BoxEnemy>(Vector2D(400.0f, 520.0f));
			//	}
			//	break;

			//default:
			//	//CreateObject<BoxEnemy>(Vector2D(100.0f, 320.0f));
			//	break;

			//
			//}
		
	/*}*/
	//制限時間が無くなったらの処理
	if (GameTime < 0)
	{
		//秒数を0にする
		GameTime = 0;
	}

	
}

//描画処理
void Scene::Draw() const
{
	//背景画像の描画
	DrawExtendGraph(0.0, 0.0, 940.0, 640.0, bg, FALSE);
	//画面の一番下に黒い四角形の図形の描画
	DrawBoxAA(0.0, 580.0, 941.0, 650.0, GetColor(0, 0, 0), TRUE);
	//タイマーの画像の描画
	DrawGraph(30.0, 588.0, ti, FALSE);
	//DrawFormatString(400.0, 300, GetColor(0, 0, 0), "%d", r, TRUE);
	//スコアという文字の画像の描画
	DrawExtendGraph(230.0, 588.0,350.0,645.0, si, FALSE);
	//ハイスコアという文字の画像の描画
	DrawExtendGraph(530.0, 584.0,700.0,645.0, hsi, FALSE);
	//制限時間の描画
	DrawExtendGraph(90.0, 588.0,140.0,645.0, number[GameTime / 150/10], FALSE);     //10の位
	DrawExtendGraph(141.0, 588.0, 190.0, 645.0, number[GameTime / 150 % 10], FALSE);    //1の位
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

	//画像の解放
	DeleteGraph(number[0]);
	DeleteGraph(number[1]);
	DeleteGraph(number[2]);
	DeleteGraph(number[3]);
	DeleteGraph(number[4]);
	DeleteGraph(number[5]);
	DeleteGraph(number[6]);
	DeleteGraph(number[7]);
	DeleteGraph(number[8]);
	DeleteGraph(number[9]);
	
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
		//being = FALSE;
	}
}
#endif // D_PIVOT_CENTER


