#pragma once
#define TIMELIMIT (9000)  //制限時間（1分）

#define POSITION_Y_0 (520.0f)
#define POSITION_Y_1 (520.0f)
#define POSITION_Y_2 (210.0f)
#define POSITION_Y_3 (360.0f)

#include  "../Objects/GameObject.h"
#include "DxLib.h"
#include <vector>

class Scene
{
private:
	std::vector<GameObject*> objects;  //オブジェクトリスト
	int bg;  //背景画像
	int ti;  //タイマーの画像
	int number[10];   //数字の画像
	int si;    //スコアという文字の画像
	int hsi;   //ハイスコアという文字の画像
	int GameTime;  //スタート時間
	bool being;    //爆弾を出すか出さないか
	bool e_flg;  //敵のフラグ
	int t_count;		//経過時間
	int result_count;	//間を開けて結果を出すための変数
	int RandamEnemy;	//敵をランダムに出すための変数
	int SumScore;		//合計スコア
	int  Result[5];   //リザルトの画像
	int  ResultImage;   //リザルトの画像を格納する変数
	int main_bgm[2];		//BGM
	int result_se[4];	//SE
	int ResultSE;	//SEの音源を格納する変数
public:
	Scene();
	~Scene();
	int r;     //敵をランダムに出現させるための変数
	void Initialize();
	void Update();
	void Draw() const;
	void TimeUpDraw() const;
	void Finalize();
	void ResultScene();

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);
	//ランダムに敵を出す
	//void 
	
	//オブジェクト生成処理
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//指定したクラスを生成する
		T* new_instance = new T();
		//GameObjectクラスを継承しているか確認
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//エラーチェック
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("ゲームオブジェクトが生成できませんでした\n");
		}

		//初期化処理
		new_object->Initialize();

		//位置情報の設定
		new_object->SetLocation(location);

		//シーン内に存在するオブジェクトリストに追加
		objects.push_back(new_object);

		//インスタンスのポインタを返却
		return new_instance;
	}
};