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

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() : objects(),bg(0),ti(0),si(0),hsi(0),GameTime(0),r(0), e_flg(FALSE)
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
	being = FALSE;
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
	//�w�i�摜�̓Ǎ���
	bg = LoadGraph("Resource/Images/BackGround.png");   
	//�^�C�}�[�̉摜�̓Ǎ���
	ti = LoadGraph("Resource/Images/TimeLimit/timer-03.png");     
	//�����̉摜�̓Ǎ���
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
	//�X�R�A�Ƃ��������̉摜�̓Ǎ���
	si = LoadGraph("Resource/Images/Score/font-21.png");
	//�n�C�X�R�A�Ƃ��������̉摜�̓Ǎ���
	hsi = LoadGraph("Resource/Images/Score/hs.png");
	//�������Ԃ̏�����
	GameTime = TIMELIMIT;
	

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

	//�I�u�W�F�N�g���m������������A���ꂼ��I�u�W�F�N�g������
	for (int i = 0; i < objects.size(); i++)
	{
		

		if (objects[i]->EffaceObjects()==TRUE)
		{
			
			being = FALSE;
			e_flg = FALSE;

			if (objects[i]->GetObjectType() == BOMB)
			{
				Vector2D bp;
				bp = objects[i]->GetLocation();   //���e�̌��݈ʒu

				CreateObject<BombBlast>(bp);
			}

			objects.erase(objects.begin() + i);
			//continue;
		}
	}

	//���e����ʉ��ɓ��B���������
	for (int i = 0; i < objects.size(); i++)
	{
		
		if (dynamic_cast<Bomb*>(objects[i]) != nullptr)
		{
			Vector2D bp;
			bp = objects[i]->GetLocation();   //���e�̌��݈ʒu
			if (bp.y>532.0)
			{
				objects.erase(objects.begin() + i);
				being = FALSE;
				CreateObject<BombBlast>(bp);
			}
		}
	}

	//�G����ʍ��E�ɓ��B���������
	for (int i = 0; i < objects.size(); i++)
	{

		if (dynamic_cast<BoxEnemy*>(objects[i]) != nullptr)
		{
			Vector2D bep;
			bep = objects[i]->GetLocation();   //�G�̌��݈ʒu
			if (bep.x > 900.0||bep.x < 50.0)
			{
				objects.erase(objects.begin() + i);
				e_flg = FALSE;
			}
		}
	}
	

	//��ʏ�ɔ��e���������
	if (being==FALSE)
	{
		//�X�y�[�X�L�[����������A���e�𐶐�
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

	//Z�L�[����������A�G�𐶐�
	/*if (InputControl::GetKeyDown(KEY_INPUT_Z))
	{
		
	}*/
	/*while (GameTime>0)
	{*/
		

			
		
/*}*/
	//�������Ԃ̍X�V
	GameTime--;
	
	/*if (GameTime == 54 || GameTime == 48 || GameTime == 42 || GameTime == 36 || GameTime == 30 || GameTime == 24 || GameTime == 18 || GameTime == 12 || GameTime == 6)
	{*/
		int GetRand(10);
		int r = GetRand % 10 + 1;
		//int SRand(r);
		if (e_flg == FALSE)
		{
			if (GameTime / 150 % 6 == 0)
			{
				CreateObject<BoxEnemy>(Vector2D(80.0f, 520.0f));
				e_flg = TRUE;
			}
		}
			//switch (GetRand % 10 + 1)
			//{
			//case 1:
			//	
			//	break;

			//case 2:
			//	if (GameTime / 150 % 6 == 0)
			//	{
			//		CreateObject<BoxEnemy>(Vector2D(200.0f, 520.0f));
			//	}
			//	break;

			//case 3:
			//	if (GameTime / 150 % 6 == 0)
			//	{
			//		CreateObject<BoxEnemy>(Vector2D(300.0f, 520.0f));
			//	}
			//	break;

			//case 4:
			//	if (GameTime / 150 % 6 == 0)
			//	{
			//		CreateObject<BoxEnemy>(Vector2D(400.0f, 520.0f));
			//	}
			//	break;

			//default:
			//	//CreateObject<BoxEnemy>(Vector2D(100.0f, 320.0f));
			//	break;

			//
			//}
		
	/*}*/
	//�������Ԃ������Ȃ�����̏���
	if (GameTime < 0)
	{
		//�b����0�ɂ���
		GameTime = 0;
	}

	
}

//�`�揈��
void Scene::Draw() const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0.0, 0.0, 940.0, 640.0, bg, FALSE);
	//��ʂ̈�ԉ��ɍ����l�p�`�̐}�`�̕`��
	DrawBoxAA(0.0, 580.0, 941.0, 650.0, GetColor(0, 0, 0), TRUE);
	//�^�C�}�[�̉摜�̕`��
	DrawGraph(30.0, 588.0, ti, FALSE);
	//DrawFormatString(400.0, 300, GetColor(0, 0, 0), "%d", r, TRUE);
	//�X�R�A�Ƃ��������̉摜�̕`��
	DrawExtendGraph(230.0, 588.0,350.0,645.0, si, FALSE);
	//�n�C�X�R�A�Ƃ��������̉摜�̕`��
	DrawExtendGraph(530.0, 584.0,700.0,645.0, hsi, FALSE);
	//�������Ԃ̕`��
	DrawExtendGraph(90.0, 588.0,140.0,645.0, number[GameTime / 150/10], FALSE);     //10�̈�
	DrawExtendGraph(141.0, 588.0, 190.0, 645.0, number[GameTime / 150 % 10], FALSE);    //1�̈�
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

	//�摜�̉��
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
		//being = FALSE;
	}
}
#endif // D_PIVOT_CENTER


