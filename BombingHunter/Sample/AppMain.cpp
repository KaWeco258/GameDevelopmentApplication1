#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Scene/Scene.h"

//��������v���O�������n�߂�

//���C���֐�
int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y�i���F640px,�c�F480px�j��ݒ�
	SetGraphMode(640, 480, 32);

	//Dx���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		return -1;
	}

	//���[�J���ϐ���`
	Scene* scene = new Scene();  //�V�[�����
	GameObject* object = new GameObject();  //�V�[�����
	int result = 0;              //�I����ԏ��

	//����ʂ���`����s��
	SetDrawScreen(DX_SCREEN_BACK);

	try
	{
		//�V�[���̏���������
		scene->Initialize();
		object->Initialize();

		//���C�����[�v
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			//�X�V����
			InputControl::Update();

			//�V�[���̍X�V����
			scene->Update();
			object->Update();

			//��ʂ̏�����
			ClearDrawScreen();

			//�V�[���̕`�揈��
			scene->Draw();
			object->Draw();

			//����ʂ̓��e��\��ʔ��f
			ScreenFlip();
		}


	}
	catch (const char* error_log)
	{
		//�G���[����Log.txt�ɏo�͂���
		OutputDebugString(error_log);
		//�ُ��ԂɕύX����
		result = -1;
	}

	//�V�[���̏��̍폜����
	if (scene != nullptr)
	{
		scene->Finalize();
		object->Finalize();
		delete scene;
		delete object;
		scene = nullptr;
		object = nullptr;
	}


	//Dx���C�u�����̎g�p�̏I������
	DxLib_End();

	//�I����Ԃ�ʒm
	return result;
}