#include "DxLib.h"
#include "Utility/InputControl.h"
#include "Scene/Scene.h"

//��������v���O�������n�߂�

//���C���֐�
int WINAPI WinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nShowCmd)
{
	//�E�B���h�E���[�h�ŋN��
	ChangeWindowMode(TRUE);

	//�E�B���h�E�T�C�Y�i���F640px,�c�F480px�j��ݒ�
	SetGraphMode(940, 580, 32);

	//Dx���C�u�����̏���������
	if (DxLib_Init() == -1)
	{
		//�ُ��ʒm
		return -1;
	}
	

	//���[�J���ϐ���`
	Scene* scene = new Scene();  //�V�[���𐶐�
	int result = 0;              //�I����ԏ��

	//����ʂ���`����s��
	SetDrawScreen(DX_SCREEN_BACK);
	

	try
	{
		//�V�[���̏���������
		scene->Initialize();

		//���C�����[�v
		//ESC�L�[�������ꂽ��A���[�v���I��
		while (ProcessMessage() != -1 && CheckHitKey(KEY_INPUT_ESCAPE) != TRUE)
		{
			int bg=LoadGraph("Resource/Images/BackGround.png");
			DrawRotaGraphF(640.0, 480.0, 1.0, 0.0, bg, TRUE);

			//�X�V����
			InputControl::Update();

			//�V�[���̍X�V����
			scene->Update();

			//��ʂ̏�����
			ClearDrawScreen();

			//�V�[���̕`�揈��
			scene->Draw();

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
		delete scene;
		scene = nullptr;
	}


	//Dx���C�u�����̎g�p�̏I������
	DxLib_End();

	//�I����Ԃ�ʒm
	return result;
}