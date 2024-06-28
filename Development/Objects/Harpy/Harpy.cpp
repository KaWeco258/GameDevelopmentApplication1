#include "Harpy.h"
#include "DxLib.h"
#include "../Bomb/Bomb.h"

//�R���X�g���N�^
Harpy::Harpy() : animation_count(0), direction(0.0f)
{
	harpy_animation[0] = NULL;
	harpy_animation[1] = NULL;


}

//�f�X�g���N�^
Harpy::~Harpy()
{

}

//����������
void Harpy::Initialize()
{
	//�摜�̓ǂݍ���
	harpy_animation[0] = LoadGraph("Resource/Images/Harpy/1.png");
	harpy_animation[1] = LoadGraph("Resource/Images/Harpy/2.png");
	

	//�G���[�`�F�b�N
	if (harpy_animation[0] == -1 || harpy_animation[1] == -1)
	{
		throw("�n�[�s�[�̉摜������܂���\n");
	}
	
	//0�C1�Ő������擾
	//int r = GetRand(1);

	//���G�̃X�s�[�h�������_���ɐݒ肷��
	speed = 0.0f;

	////r��0�Ȃ獶����o���A1�Ȃ�E����o��
	//if (r == 0)
	//{
	//	//�E
	//	direction = Vector2D(speed, 0.0f);
	//	this->location.x = 80.0f;
	//}
	//else
	//{
	//	//��
	//	direction = Vector2D(-speed, 0.0f);
	//	this->location.x = 800.0f;
	//}


	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	boxenemy_image = harpy_animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.0f);


}

//�X�V����
void Harpy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Harpy::Draw() const
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

	//�������ƂɃn�[�s�[�摜��`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, harpy_image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Harpy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(harpy_animation[0]);
	DeleteGraph(harpy_animation[1]);
	
}


//�ړ�����
void Harpy::Movement()
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

//�ړ������̐ݒ�
Vector2D Harpy::SetDirection(Vector2D& E_direction)
{
	return this->direction.x = E_direction.x;
}

//�����蔻��ʒm����
void Harpy::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	//direction = 0.0f;

	//���e�ɓ������Ė���������
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		score = -50;
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
void Harpy::AnimationControl()
{
	//�A�j���[�V�����J�E���g���v�Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�����Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (harpy_image == harpy_animation[0])
		{
			harpy_image = harpy_animation[1];
		}
		else
		{
			harpy_image = harpy_animation[0];
		}

		
		
	}
}