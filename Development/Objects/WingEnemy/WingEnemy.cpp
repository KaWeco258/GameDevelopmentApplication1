#include "WingEnemy.h"
#include "DxLib.h"
#include "../Bomb/Bomb.h"

//�R���X�g���N�^
WingEnemy::WingEnemy() : animation_count(0), direction(0.0f)
{
	wingenemy_animation[0] = NULL;
	wingenemy_animation[1] = NULL;


}

//�f�X�g���N�^
WingEnemy::~WingEnemy()
{

}

//����������
void WingEnemy::Initialize()
{
	//�摜�̓ǂݍ���
	wingenemy_animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	wingenemy_animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");

	//�G���[�`�F�b�N
	if (wingenemy_animation[0] == -1 || wingenemy_animation[1] == -1)
	{
		throw("�n�l�e�L�̉摜������܂���\n");
	}
	
	//0�C1�Ő������擾
	int r = GetRand(1);

	//���G�̃X�s�[�h�������_���ɐݒ肷��
	float speed = (GetRand(2) % 2 * 0.5) + 1.0f;

	//r��0�Ȃ獶����o���A1�Ȃ�E����o��
	if (r == 0)
	{
		//�E
		direction = Vector2D(speed, 0.0f);
		this->location.x = 80.0f;
	}
	else
	{
		//��
		direction = Vector2D(-speed, 0.0f);
		this->location.x = 800.0f;
	}


	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	wingenemy_image = wingenemy_animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.0f);


}

//�X�V����
void WingEnemy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void WingEnemy::Draw() const
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

	//�������ƂɃn�l�e�L�摜��`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, wingenemy_image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void WingEnemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(wingenemy_animation[0]);
	DeleteGraph(wingenemy_animation[1]);
}


//�ړ�����
void WingEnemy::Movement()
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
Vector2D WingEnemy::SetDirection(Vector2D& E_direction)
{
	return this->direction.x = E_direction.x;
}

//�����蔻��ʒm����
void WingEnemy::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	//direction = 0.0f;


	//���e�ɓ������Ė���������
	if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	{
		score = 50;
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
void WingEnemy::AnimationControl()
{
	//�A�j���[�V�����J�E���g���v�Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�����Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (wingenemy_image == wingenemy_animation[0])
		{
			wingenemy_image = wingenemy_animation[1];
		}
		else
		{
			wingenemy_image = wingenemy_animation[0];
		}
	}
}