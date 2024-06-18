#pragma once
#define TIMELIMIT (600*15)  //制限時間（1分）

#include  "../Objects/GameObject.h"
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

public:
	Scene();
	~Scene();

	void Initialize();
	void Update();
	void Draw() const;
	void Finalize();

private:
	//当たり判定チェック処理
	void HitCheckObject(GameObject* a, GameObject* b);
	
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