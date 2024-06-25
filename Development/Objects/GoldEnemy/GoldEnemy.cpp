#include "GoldEnemy.h"
#include "DxLib.h"
#include "../Bomb/Bomb.h"

//�R���X�g���N�^
GoldEnemy::GoldEnemy() : animation_count(0), direction(0.0f)
{
	goldenemy_animation[0] = NULL;
	goldenemy_animation[1] = NULL;
	goldenemy_animation[2] = NULL;
	goldenemy_animation[3] = NULL;
	goldenemy_animation[4] = NULL;


}

//�f�X�g���N�^
GoldEnemy::~GoldEnemy()
{

}

//����������
void GoldEnemy::Initialize()
{
	//�摜�̓ǂݍ���
	goldenemy_animation[0] = LoadGraph("Resource/Images/GoldEnemy/1.png");
	goldenemy_animation[1] = LoadGraph("Resource/Images/GoldEnemy/2.png");
	goldenemy_animation[2] = LoadGraph("Resource/Images/GoldEnemy/3.png");
	goldenemy_animation[3] = LoadGraph("Resource/Images/GoldEnemy/4.png");
	goldenemy_animation[4] = LoadGraph("Resource/Images/GoldEnemy/5.png");
	

	//�G���[�`�F�b�N
	if (goldenemy_animation[0] == -1 || goldenemy_animation[1] == -1 || goldenemy_animation[2] == -1 || goldenemy_animation[3] == -1 || goldenemy_animation[4] == -1)
	{
		throw("�S�[���h�e�L�̉摜������܂���\n");
	}
	
	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	goldenemy_image = goldenemy_animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.0f);


}

//�X�V����
void GoldEnemy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void GoldEnemy::Draw() const
{
	//�摜�t���O
	int flip_flag = FALSE;

	//�i�s�����ɂ���āA���]��Ԃ����肷��
	if (direction.x > 0.0f)
	{
		flip_flag = FALSE;
	}
	else
	{
		flip_flag = TRUE;
	}

	//�������ƂɃL���e�L�摜��`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, goldenemy_image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void GoldEnemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(goldenemy_animation[0]);
	DeleteGraph(goldenemy_animation[1]);
	DeleteGraph(goldenemy_animation[2]);
	DeleteGraph(goldenemy_animation[3]);
	DeleteGraph(goldenemy_animation[4]);
	
}


//�ړ�����
void GoldEnemy::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]������
	/*if (((location.x + direction.x) < box_size.x) ||
		(940.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(580.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}*/

	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}

//�����蔻��ʒm����
void GoldEnemy::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	//direction = 0.0f;

	//���e�ɓ������Ė���������
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		//�G��`�悵������
		Efface = TRUE;
	}
	//���e�ɓ���������
	else
	{
		//�G����������
		Efface = FALSE;
	}
}


//�A�j���[�V��������
void GoldEnemy::AnimationControl()
{
	//�A�j���[�V�����J�E���g���v�Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�����Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (goldenemy_image == goldenemy_animation[0])
		{
			goldenemy_image = goldenemy_animation[1];
		}
		else if (goldenemy_image == goldenemy_animation[1])
		{
			goldenemy_image = goldenemy_animation[2];
		}
		else if (goldenemy_image == goldenemy_animation[2])
		{
			goldenemy_image = goldenemy_animation[3];
		}
		else if (goldenemy_image == goldenemy_animation[3])
		{
			boxenemy_image = goldenemy_animation[4];
		}
		else if (goldenemy_image == goldenemy_animation[4])
		{
			goldenemy_image == goldenemy_animation[0];
		}

		
	}
}