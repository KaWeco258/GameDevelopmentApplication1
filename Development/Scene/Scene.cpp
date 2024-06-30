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
#include <stdlib.h>

#define D_PIVOT_CENTER

//コンストラクタ
Scene::Scene() : objects(),bg(0),ti(0),si(0),hsi(0),GameTime(0),r(0), e_flg(FALSE),t_count(0),being(FALSE),ResultImage(0),RandamEnemy(0),SumScore(0)
{
	//番号の画像の初期化
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
	//リザルトの画像の初期化
	Result[0] = NULL;
	Result[1] = NULL;
	Result[2] = NULL;
	Result[3] = NULL;
	Result[4] = NULL;
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
	//リザルトの画像の読込み
	Result[0] = LoadGraph("Resource/Images/Evalution/Finish.png");
	Result[1] = LoadGraph("Resource/Images/Evalution/BAD.png");
	Result[2] = LoadGraph("Resource/Images/Evalution/OK.png");
	Result[3] = LoadGraph("Resource/Images/Evalution/GOOD.png");
	Result[4] = LoadGraph("Resource/Images/Evalution/Perfect.png");
	//スコアという文字の画像の読込み
	si = LoadGraph("Resource/Images/Score/font-21.png");
	//ハイスコアという文字の画像の読込み
	hsi = LoadGraph("Resource/Images/Score/hs.png");
	//BGMの読込み
	main_bgm[0] = LoadSoundMem("Resource/Sounds/Evalution/BGM_arrows.wav");
	main_bgm[1] = LoadSoundMem("Resource/Sounds/Evalution/BGM_timeup.wav");
	//SEの読込み
	result_se[0] = LoadSoundMem("Resource/Sounds/Evalution/SE_bad.wav");
	result_se[1] = LoadSoundMem("Resource/Sounds/Evalution/SE_ok.wav");
	result_se[2] = LoadSoundMem("Resource/Sounds/Evalution/SE_good.wav");
	result_se[3] = LoadSoundMem("Resource/Sounds/Evalution/SE_perfect.wav");
	//制限時間の初期化
	GameTime = TIMELIMIT;
	//経過時間の初期化
	t_count = 0;
	result_count = 0;

	//0になったらフィニッシュと表示させる用の変数
	ResultImage = Result[0];
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

			SumScore += objects[i]->GetScore();

			if (SumScore < 0)
			{
				SumScore = 0;
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
		//箱敵
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

		//羽敵
		if (dynamic_cast<WingEnemy*>(objects[i]) != nullptr)
		{
			Vector2D bep;
			bep = objects[i]->GetLocation();   //敵の現在位置
			if (bep.x > 900.0 || bep.x < 50.0)
			{
				objects.erase(objects.begin() + i);
				e_flg = FALSE;
			}
		}

		//金敵
		if (dynamic_cast<GoldEnemy*>(objects[i]) != nullptr)
		{
			Vector2D bep;
			bep = objects[i]->GetLocation();   //敵の現在位置
			if (bep.x > 900.0 || bep.x < 50.0)
			{
				objects.erase(objects.begin() + i);
				e_flg = FALSE;
			}
		}

		//ハーピー
		if (dynamic_cast<Harpy*>(objects[i]) != nullptr)
		{
			Vector2D bep;
			bep = objects[i]->GetLocation();   //敵の現在位置
			if (bep.x > 900.0 || bep.x < 50.0)
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


	Vector2D E_location;
	Vector2D E_Direction;
	int r = GetRand(1);		//0，1で数字を取得

	//箱敵のスピードをランダムに設定する
	E_Direction.x = (GetRand(2) % 2 * 0.5) + 1.0f;

	//rが0なら左から出現、1なら右から出現
	if (r == 0)
	{
		//右
		E_Direction.x = E_Direction.x * 1;
		E_location.x = 70.0f;
	}
	else
	{
		//左
		E_Direction.x = E_Direction.x * -1;
		E_location.x = 900.0f;
	}

	//経過時間を加算
	t_count++;
	if (t_count >= 120)
	{
		//0～8までの乱数を取得
		RandamEnemy = GetRand(5);

		if (RandamEnemy == 0)
		{
			CreateObject<BoxEnemy>(Vector2D(E_location.x, POSITION_Y_0))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 1)
		{
			CreateObject<GoldEnemy>(Vector2D(E_location.x, POSITION_Y_1))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 2)
		{
			CreateObject<WingEnemy>(Vector2D(E_location.x, POSITION_Y_2))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 3)
		{
			CreateObject<WingEnemy>(Vector2D(E_location.x, POSITION_Y_3))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 4)
		{
			CreateObject<Harpy>(Vector2D(E_location.x, POSITION_Y_2))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 5)
		{
			CreateObject<Harpy>(Vector2D(E_location.x, POSITION_Y_3))->SetDirection(E_Direction);
		}

		t_count = 0;
	}
			
	//BGMの再生
	PlaySoundMem(main_bgm[0], DX_PLAYTYPE_LOOP, FALSE);
	
	
	
		
		
	//制限時間の更新
	GameTime--;
	
	//制限時間が無くなったらの処理
	if (GameTime < 0)
	{
		//秒数を0にする
		GameTime = 0;
		//再生を止める
		StopSoundMem(main_bgm[0]);
		//BGMの再生
		PlaySoundMem(main_bgm[1], DX_PLAYTYPE_NORMAL, FALSE);
		//SEの再生
		PlaySoundMem(ResultSE, DX_PLAYTYPE_NORMAL, FALSE);
		
		ResultScene();
		TimeUpDraw();
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
	//制限時間の描画
	DrawExtendGraph(90.0, 588.0,140.0,645.0, number[GameTime / 150/10], TRUE);			//10の位
	DrawExtendGraph(141.0, 588.0, 190.0, 645.0, number[GameTime / 150 % 10], TRUE);		//1の位
	//DrawFormatString(141.0, 588.0, GetColor(255,0,0),"%d", GameTime / 150 , TRUE);		
	//スコアという文字の画像の描画
	DrawExtendGraph(230.0, 588.0,350.0,645.0, si, FALSE);
	//
	//DrawFormatString(420.0, 408.0, GetColor(0, 0, 0), "%d", SumScore, TRUE);
	DrawExtendGraph(370.0, 588.0, 420.0, 645.0, number[SumScore / 1000], TRUE);
	DrawExtendGraph(420.0, 588.0, 470.0, 645.0, number[(SumScore%1000)/100], TRUE);
	DrawExtendGraph(470.0, 588.0, 520.0, 645.0, number[(SumScore%1000%100)/10], TRUE);
	DrawExtendGraph(520.0, 588.0, 570.0, 645.0, number[(SumScore%1000%100)%10], TRUE);
	//ハイスコアという文字の画像の描画
	//DrawExtendGraph(530.0, 584.0,700.0,645.0, hsi, FALSE);

	
	
	//DrawFormatString(300, 500, GetColor(0, 0, 0),"%d",r, TRUE);
	//オブジェクトリスト内のオブジェクトを描画
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//制限時間が0の時の描画処理
void Scene::TimeUpDraw() const
{
	//背景画像の描画
	DrawExtendGraph(0.0, 0.0, 940.0, 640.0, bg, FALSE);
	
	//画面の一番下に黒い四角形の図形の描画
	DrawBoxAA(0.0, 580.0, 941.0, 650.0, GetColor(0, 0, 0), TRUE);
	//タイマーの画像の描画
	DrawGraph(30.0, 588.0, ti, FALSE);
	//制限時間の描画
	DrawExtendGraph(90.0, 588.0, 140.0, 645.0, number[GameTime / 150 / 10], TRUE);			//10の位
	DrawExtendGraph(141.0, 588.0, 190.0, 645.0, number[GameTime / 150 % 10], TRUE);		//1の位
	//DrawFormatString(141.0, 588.0, GetColor(255,0,0),"%d", GameTime / 150 , TRUE);		
	//スコアという文字の画像の描画
	DrawExtendGraph(230.0, 588.0, 350.0, 645.0, si, FALSE);
	//
	//DrawFormatString(420.0, 408.0, GetColor(0, 0, 0), "%d", SumScore, TRUE);
	DrawExtendGraph(370.0, 588.0, 420.0, 645.0, number[SumScore / 1000], TRUE);
	DrawExtendGraph(420.0, 588.0, 470.0, 645.0, number[(SumScore % 1000) / 100], TRUE);
	DrawExtendGraph(470.0, 588.0, 520.0, 645.0, number[(SumScore % 1000 % 100) / 10], TRUE);
	DrawExtendGraph(520.0, 588.0, 570.0, 645.0, number[(SumScore % 1000 % 100) % 10], TRUE);
	//ハイスコアという文字の画像の描画
	//DrawExtendGraph(530.0, 584.0,700.0,645.0, hsi, FALSE);



		
		//
		DrawGraph(470, 325,  ResultImage, TRUE);
		DrawRotaGraph(470, 325, 1, 0, ResultImage, FALSE, FALSE);
	

	
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
	//音源の解放
	DeleteSoundMem(main_bgm[0]);
	DeleteSoundMem(main_bgm[1]);
	DeleteSoundMem(result_se[0]);
	DeleteSoundMem(result_se[1]);
	DeleteSoundMem(result_se[2]);
	DeleteSoundMem(result_se[3]);

	
}

void Scene::ResultScene()
{
	TimeUpDraw();
	//動的配列の解放
	objects.clear();

	result_count++;
	if (result_count > 300)
	{
		//スコアによって結果を変える
		if (SumScore >= 1100)
		{
			//パーフェクト
			ResultImage = Result[4];
			ResultSE = result_se[3];
		}
		else if (SumScore >= 850)
		{
			//グッド
			ResultImage = Result[3];
			ResultSE = result_se[2];
		}
		else if (SumScore >= 600)
		{
			//オーケー
			ResultImage = Result[2];
			ResultSE = result_se[1];
		}
		else
		{
			//バッド
			ResultImage = Result[1];
			ResultSE = result_se[0];

		}

	}

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


