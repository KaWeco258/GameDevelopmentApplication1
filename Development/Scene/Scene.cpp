#include "Scene.h"
#include "../Objects/Enemy/Enemy.h"
#include "../Objects/Player/Player.h"
#include "../Utility/InputControl.h"
#include "DxLib.h"
#include "../Objects/Bomb/Bomb.h"

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() : objects(),bg(0),ti(0)
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
}

//�f�X�g���N�^
Scene::~Scene()
{
	//�Y��h�~
	Finalize();
}

//����������
void Scene::Initialize()
{
	bg = LoadGraph("Resource/Images/BackGround.png");
	ti = LoadGraph("Resource/Images/TimeLimit/timer-03.png");
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
	

	//�v���C���[�𐶐�����
	CreateObject<Player>(Vector2D(320.0f, 50.0f));
}

//�X�V����
void Scene::Update()
{
	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g���X�V
	for (GameObject* obj : objects)
	{
		obj->Update();
	}

	//�I�u�W�F�N�g���m�̓����蔻��`�F�b�N
	for (int i = 0; i < objects.size(); i++)
	{
		for (int j = i + 1; j < objects.size(); j++)
		{
			//�����蔻��`�F�b�N����
			HitCheckObject(objects[i], objects[j]);
		}
	}

	//Z�L�[����������A�G�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		CreateObject<Enemy>(Vector2D(100.0f, 520.0f));
	}

	//�X�y�[�X�L�[����������A���e�𐶐�
	if (InputControl::GetKeyDown(KEY_INPUT_SPACE))
	{
		for (int i = 0; i < objects.size(); i++)
		{
			if (dynamic_cast<Player*>(objects[i]) != nullptr)
			{
				CreateObject<Bomb>(objects[i]->GetLocation());
			}
		}
		
	}

	
}

//�`�揈��
void Scene::Draw() const
{
	DrawExtendGraph(0.0, 0.0, 940.0, 640.0, bg, FALSE);
	DrawBoxAA(0.0, 580.0, 941.0, 650.0, GetColor(0, 0, 0), TRUE);
	DrawGraph(40.0, 588.0, ti, FALSE);


	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�I��������
void Scene::Finalize()
{
	//���I�z�񂪋�Ȃ珈�����I������
	if (objects.empty())
	{
		return;
	}

	//�e�I�u�W�F�N�g���폜����
	for (GameObject* obj : objects)
	{
		obj->Finalize();
		delete obj;
	}

	//���I�z��̉��
	objects.clear();
}

#ifdef D_PIVOT_CENTER

//�����蔻��`�F�b�N����(��`�̒��S�œ����蔻����Ƃ�)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//2�̃I�u�W�F�N�g�̋������擾
	Vector2D diff = a->GetLocation() - b->GetLocation();

	//2�̃I�u�W�F�N�g�̓����蔻��̑傫�����擾
	Vector2D box_size = (a->GetBoxSize() + b->GetBoxSize()) / 2.0f;

	//�������傫�����傫���ꍇ�AHit����Ƃ���
	if ((fabsf(diff.x) < box_size.x) && (fabsf(diff.y) < box_size.y))
	{
		//�����������Ƃ��I�u�W�F�N�g�ɒʒm
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#else

//�����蔻��`�F�b�N����(���㒸�_�̍��W���瓖���蔻��v�Z���s��)
void Scene::HitCheckObject(GameObject* a, GameObject* b)
{
	//�E�����_���W���擾����
	Vector2D a_lower_right = a->Getlocation() + a->GetBoxSize();
	Vector2D b_lower_right = b->Getlocation() + b->GetBoxSize();

	//��`A�Ƌ�`B�̈ʒu�֌W�𒲂ׂ�
	if ((a->GetLocation().x < b_lower_right.x) &&
		(a->GetLocation().y < b_lower_right.y) &&
		(a_lower_right.x > b->GetLocation().x) &&
		(a_lower_right.y > b->GetLocation().y))
	{
		//�I�u�W�F�N�g�ɑ΂���HIT�����ʒm
		a->OnHitCollision(b);
		b->OnHitCollision(a);
	}
}
#endif // D_PIVOT_CENTER
