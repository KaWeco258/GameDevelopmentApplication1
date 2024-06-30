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
#include <stdlib.h>

#define D_PIVOT_CENTER

//�R���X�g���N�^
Scene::Scene() : objects(),bg(0),ti(0),si(0),hsi(0),GameTime(0),r(0), e_flg(FALSE),t_count(0),being(FALSE),ResultImage(0),RandamEnemy(0),SumScore(0)
{
	//�ԍ��̉摜�̏�����
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
	//���U���g�̉摜�̏�����
	Result[0] = NULL;
	Result[1] = NULL;
	Result[2] = NULL;
	Result[3] = NULL;
	Result[4] = NULL;
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
	//���U���g�̉摜�̓Ǎ���
	Result[0] = LoadGraph("Resource/Images/Evalution/Finish.png");
	Result[1] = LoadGraph("Resource/Images/Evalution/BAD.png");
	Result[2] = LoadGraph("Resource/Images/Evalution/OK.png");
	Result[3] = LoadGraph("Resource/Images/Evalution/GOOD.png");
	Result[4] = LoadGraph("Resource/Images/Evalution/Perfect.png");
	//�X�R�A�Ƃ��������̉摜�̓Ǎ���
	si = LoadGraph("Resource/Images/Score/font-21.png");
	//�n�C�X�R�A�Ƃ��������̉摜�̓Ǎ���
	hsi = LoadGraph("Resource/Images/Score/hs.png");
	//BGM�̓Ǎ���
	main_bgm[0] = LoadSoundMem("Resource/Sounds/Evalution/BGM_arrows.wav");
	main_bgm[1] = LoadSoundMem("Resource/Sounds/Evalution/BGM_timeup.wav");
	//SE�̓Ǎ���
	result_se[0] = LoadSoundMem("Resource/Sounds/Evalution/SE_bad.wav");
	result_se[1] = LoadSoundMem("Resource/Sounds/Evalution/SE_ok.wav");
	result_se[2] = LoadSoundMem("Resource/Sounds/Evalution/SE_good.wav");
	result_se[3] = LoadSoundMem("Resource/Sounds/Evalution/SE_perfect.wav");
	//�������Ԃ̏�����
	GameTime = TIMELIMIT;
	//�o�ߎ��Ԃ̏�����
	t_count = 0;
	result_count = 0;

	//0�ɂȂ�����t�B�j�b�V���ƕ\��������p�̕ϐ�
	ResultImage = Result[0];
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

			SumScore += objects[i]->GetScore();

			if (SumScore < 0)
			{
				SumScore = 0;
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
		//���G
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

		//�H�G
		if (dynamic_cast<WingEnemy*>(objects[i]) != nullptr)
		{
			Vector2D bep;
			bep = objects[i]->GetLocation();   //�G�̌��݈ʒu
			if (bep.x > 900.0 || bep.x < 50.0)
			{
				objects.erase(objects.begin() + i);
				e_flg = FALSE;
			}
		}

		//���G
		if (dynamic_cast<GoldEnemy*>(objects[i]) != nullptr)
		{
			Vector2D bep;
			bep = objects[i]->GetLocation();   //�G�̌��݈ʒu
			if (bep.x > 900.0 || bep.x < 50.0)
			{
				objects.erase(objects.begin() + i);
				e_flg = FALSE;
			}
		}

		//�n�[�s�[
		if (dynamic_cast<Harpy*>(objects[i]) != nullptr)
		{
			Vector2D bep;
			bep = objects[i]->GetLocation();   //�G�̌��݈ʒu
			if (bep.x > 900.0 || bep.x < 50.0)
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


	Vector2D E_location;
	Vector2D E_Direction;
	int r = GetRand(1);		//0�C1�Ő������擾

	//���G�̃X�s�[�h�������_���ɐݒ肷��
	E_Direction.x = (GetRand(2) % 2 * 0.5) + 1.0f;

	//r��0�Ȃ獶����o���A1�Ȃ�E����o��
	if (r == 0)
	{
		//�E
		E_Direction.x = E_Direction.x * 1;
		E_location.x = 70.0f;
	}
	else
	{
		//��
		E_Direction.x = E_Direction.x * -1;
		E_location.x = 900.0f;
	}

	//�o�ߎ��Ԃ����Z
	t_count++;
	if (t_count >= 120)
	{
		//0�`8�܂ł̗������擾
		RandamEnemy = GetRand(5);

		if (RandamEnemy == 0)
		{
			CreateObject<BoxEnemy>(Vector2D(E_location.x, POSITION_Y_0))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 1)
		{
			CreateObject<GoldEnemy>(Vector2D(E_location.x, POSITION_Y_1))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 2)
		{
			CreateObject<WingEnemy>(Vector2D(E_location.x, POSITION_Y_2))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 3)
		{
			CreateObject<WingEnemy>(Vector2D(E_location.x, POSITION_Y_3))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 4)
		{
			CreateObject<Harpy>(Vector2D(E_location.x, POSITION_Y_2))->SetDirection(E_Direction);
		}
		else if (RandamEnemy == 5)
		{
			CreateObject<Harpy>(Vector2D(E_location.x, POSITION_Y_3))->SetDirection(E_Direction);
		}

		t_count = 0;
	}
			
	//BGM�̍Đ�
	PlaySoundMem(main_bgm[0], DX_PLAYTYPE_LOOP, FALSE);
	
	
	
		
		
	//�������Ԃ̍X�V
	GameTime--;
	
	//�������Ԃ������Ȃ�����̏���
	if (GameTime < 0)
	{
		//�b����0�ɂ���
		GameTime = 0;
		//�Đ����~�߂�
		StopSoundMem(main_bgm[0]);
		//BGM�̍Đ�
		PlaySoundMem(main_bgm[1], DX_PLAYTYPE_NORMAL, FALSE);
		//SE�̍Đ�
		PlaySoundMem(ResultSE, DX_PLAYTYPE_NORMAL, FALSE);
		
		ResultScene();
		TimeUpDraw();
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
	//�������Ԃ̕`��
	DrawExtendGraph(90.0, 588.0,140.0,645.0, number[GameTime / 150/10], TRUE);			//10�̈�
	DrawExtendGraph(141.0, 588.0, 190.0, 645.0, number[GameTime / 150 % 10], TRUE);		//1�̈�
	//DrawFormatString(141.0, 588.0, GetColor(255,0,0),"%d", GameTime / 150 , TRUE);		
	//�X�R�A�Ƃ��������̉摜�̕`��
	DrawExtendGraph(230.0, 588.0,350.0,645.0, si, FALSE);
	//
	//DrawFormatString(420.0, 408.0, GetColor(0, 0, 0), "%d", SumScore, TRUE);
	DrawExtendGraph(370.0, 588.0, 420.0, 645.0, number[SumScore / 1000], TRUE);
	DrawExtendGraph(420.0, 588.0, 470.0, 645.0, number[(SumScore%1000)/100], TRUE);
	DrawExtendGraph(470.0, 588.0, 520.0, 645.0, number[(SumScore%1000%100)/10], TRUE);
	DrawExtendGraph(520.0, 588.0, 570.0, 645.0, number[(SumScore%1000%100)%10], TRUE);
	//�n�C�X�R�A�Ƃ��������̉摜�̕`��
	//DrawExtendGraph(530.0, 584.0,700.0,645.0, hsi, FALSE);

	
	
	//DrawFormatString(300, 500, GetColor(0, 0, 0),"%d",r, TRUE);
	//�I�u�W�F�N�g���X�g���̃I�u�W�F�N�g��`��
	for (GameObject* obj : objects)
	{
		obj->Draw();
	}
}

//�������Ԃ�0�̎��̕`�揈��
void Scene::TimeUpDraw() const
{
	//�w�i�摜�̕`��
	DrawExtendGraph(0.0, 0.0, 940.0, 640.0, bg, FALSE);
	
	//��ʂ̈�ԉ��ɍ����l�p�`�̐}�`�̕`��
	DrawBoxAA(0.0, 580.0, 941.0, 650.0, GetColor(0, 0, 0), TRUE);
	//�^�C�}�[�̉摜�̕`��
	DrawGraph(30.0, 588.0, ti, FALSE);
	//�������Ԃ̕`��
	DrawExtendGraph(90.0, 588.0, 140.0, 645.0, number[GameTime / 150 / 10], TRUE);			//10�̈�
	DrawExtendGraph(141.0, 588.0, 190.0, 645.0, number[GameTime / 150 % 10], TRUE);		//1�̈�
	//DrawFormatString(141.0, 588.0, GetColor(255,0,0),"%d", GameTime / 150 , TRUE);		
	//�X�R�A�Ƃ��������̉摜�̕`��
	DrawExtendGraph(230.0, 588.0, 350.0, 645.0, si, FALSE);
	//
	//DrawFormatString(420.0, 408.0, GetColor(0, 0, 0), "%d", SumScore, TRUE);
	DrawExtendGraph(370.0, 588.0, 420.0, 645.0, number[SumScore / 1000], TRUE);
	DrawExtendGraph(420.0, 588.0, 470.0, 645.0, number[(SumScore % 1000) / 100], TRUE);
	DrawExtendGraph(470.0, 588.0, 520.0, 645.0, number[(SumScore % 1000 % 100) / 10], TRUE);
	DrawExtendGraph(520.0, 588.0, 570.0, 645.0, number[(SumScore % 1000 % 100) % 10], TRUE);
	//�n�C�X�R�A�Ƃ��������̉摜�̕`��
	//DrawExtendGraph(530.0, 584.0,700.0,645.0, hsi, FALSE);



		
		//
		DrawGraph(470, 325,  ResultImage, TRUE);
		DrawRotaGraph(470, 325, 1, 0, ResultImage, FALSE, FALSE);
	

	
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
	//�����̉��
	DeleteSoundMem(main_bgm[0]);
	DeleteSoundMem(main_bgm[1]);
	DeleteSoundMem(result_se[0]);
	DeleteSoundMem(result_se[1]);
	DeleteSoundMem(result_se[2]);
	DeleteSoundMem(result_se[3]);

	
}

void Scene::ResultScene()
{
	TimeUpDraw();
	//���I�z��̉��
	objects.clear();

	result_count++;
	if (result_count > 300)
	{
		//�X�R�A�ɂ���Č��ʂ�ς���
		if (SumScore >= 1100)
		{
			//�p�[�t�F�N�g
			ResultImage = Result[4];
			ResultSE = result_se[3];
		}
		else if (SumScore >= 850)
		{
			//�O�b�h
			ResultImage = Result[3];
			ResultSE = result_se[2];
		}
		else if (SumScore >= 600)
		{
			//�I�[�P�[
			ResultImage = Result[2];
			ResultSE = result_se[1];
		}
		else
		{
			//�o�b�h
			ResultImage = Result[1];
			ResultSE = result_se[0];

		}

	}

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


