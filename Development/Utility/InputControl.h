#pragma once

#define D_KEYCODE_MAX (256)

class InputControl
{
private:
	//���݂̓��͒l
	static char now_key[D_KEYCODE_MAX];
	//�O��̓��͒l
	static char old_key[D_KEYCODE_MAX];

public:
	//�X�V����
	static void Update();

	//�L�[�����������Ă��邩�̔���
	static bool GetKey(int key_code);
	//�L�[���������u�Ԃ��̔���
	static bool GetKeyDown(int key_code);
	//�L�[�𗣂����u�Ԃ��̔���
	static bool GetKeyUp(int key_code);

private:
	//�L�[�R�[�h�͈͓̔����̔���
	static bool CheckKeyCodeRange(int key_code);

};