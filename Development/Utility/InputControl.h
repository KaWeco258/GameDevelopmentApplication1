#pragma once

#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	//現在の入力値
	static char now_key[D_KEYCODE_MAX];
	//前回の入力値
	static char old_key[D_KEYCODE_MAX];

public:
	//更新処理
	static void Update();

	//キーを押し続けているかの判定
	static bool GetKey(int key_code);
	//キーを押した瞬間かの判定
	static bool GetKeyDown(int key_code);
	//キーを離した瞬間かの判定
	static bool GetKeyUp(int key_code);

private:
	//キーコードの範囲内かの判定
	static bool CheckKeyCodeRange(int key_code);

};