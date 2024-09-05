#pragma once
#define TIMELIMIT (9000)  //�������ԁi1���j

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
	std::vector<GameObject*> objects;  //�I�u�W�F�N�g���X�g
	int bg;  //�w�i�摜
	int ti;  //�^�C�}�[�̉摜
	int number[10];   //�����̉摜
	int si;    //�X�R�A�Ƃ��������̉摜
	int hsi;   //�n�C�X�R�A�Ƃ��������̉摜
	int GameTime;  //�X�^�[�g����
	bool being;    //���e���o�����o���Ȃ���
	bool e_flg;  //�G�̃t���O
	int t_count;		//�o�ߎ���
	int result_count;	//�Ԃ��J���Č��ʂ��o�����߂̕ϐ�
	int RandamEnemy;	//�G�������_���ɏo�����߂̕ϐ�
	int SumScore;		//���v�X�R�A
	int  Result[5];   //���U���g�̉摜
	int  ResultImage;   //���U���g�̉摜���i�[����ϐ�
	int main_bgm[2];		//BGM
	int result_se[4];	//SE
	int ResultSE;	//SE�̉������i�[����ϐ�
public:
	Scene();
	~Scene();
	int r;     //�G�������_���ɏo�������邽�߂̕ϐ�
	void Initialize();
	void Update();
	void Draw() const;
	void TimeUpDraw() const;
	void Finalize();
	void ResultScene();

private:
	//�����蔻��`�F�b�N����
	void HitCheckObject(GameObject* a, GameObject* b);
	//�����_���ɓG���o��
	//void 
	
	//�I�u�W�F�N�g��������
	template <class T>
	T* CreateObject(const Vector2D& location)
	{
		//�w�肵���N���X�𐶐�����
		T* new_instance = new T();
		//GameObject�N���X���p�����Ă��邩�m�F
		GameObject* new_object = dynamic_cast<GameObject*>(new_instance);

		//�G���[�`�F�b�N
		if (new_object == nullptr)
		{
			delete new_instance;
			throw ("�Q�[���I�u�W�F�N�g�������ł��܂���ł���\n");
		}

		//����������
		new_object->Initialize();

		//�ʒu���̐ݒ�
		new_object->SetLocation(location);

		//�V�[�����ɑ��݂���I�u�W�F�N�g���X�g�ɒǉ�
		objects.push_back(new_object);

		//�C���X�^���X�̃|�C���^��ԋp
		return new_instance;
	}
};