#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Scene/Scene.h"

//ここからプログラムが始める

//メイン関数
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	//ウィンドウモードで起動
	ChangeWindowMode(TRUE);

	//ウィンドウサイズ（横：940px,縦：645px）を設定
	SetGraphMode(940, 645, 32);

	//Dxライブラリの初期化処理
	if (DxLib_Init() == -1)
	{
		//異常を通知
		return -1;
	}
	

	//ローカル変数定義
	Scene* scene = new Scene();  //シーンを生成
	int result = 0;              //終了状態情報

	//裏画面から描画を行う
	SetDrawScreen(DX_SCREEN_BACK);
	

	try
	{
		//シーンの初期化処理
		scene->Initialize();

		//メインループ
		//ESCキーが押されたら、ループを終了
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			

			//更新処理
			InputControl::Update();

			//シーンの更新処理
			scene->Update();

			//画面の初期化
			ClearDrawScreen();

			//シーンの描画処理
			scene->Draw();

			//
			/*if (Scene::GameTime < 0)
			{
				break;
			}*/

			//裏画面の内容を表画面反映
			ScreenFlip();
		}


	}
	catch (const char* error_log)
	{
		//エラー情報をLog.txtに出力する
		OutputDebugString(error_log);
		//異常状態に変更する
		result = -1;
	}

	//シーンの情報の削除する
	if (scene != nullptr)
	{
		scene->Finalize();
		delete scene;
		scene = nullptr;
	}


	//Dxライブラリの使用の終了処理
	DxLib_End();

	//終了状態を通知
	return result;
}