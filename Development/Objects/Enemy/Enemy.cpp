#include "Enemy.h"
#include "DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() : animation_count(0), direction(0.0f)
{
	boxenemy_animation[0] = NULL;
	boxenemy_animation[1] = NULL;
	wingenemy_animation[0] = NULL;
	wingenemy_animation[1] = NULL;

}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�摜�̓ǂݍ���
	boxenemy_animation[0] = LoadGraph("Resource/Images/BoxEnemy/1.png");
	boxenemy_animation[1] = LoadGraph("Resource/Images/BoxEnemy/2.png");
	wingenemy_animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	wingenemy_animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");

	//�G���[�`�F�b�N
	if (boxenemy_animation[0] == -1 || boxenemy_animation[1] == -1)
	{
		throw("�n�R�e�L�̉摜������܂���\n");
	}
	if (wingenemy_animation[0] == -1 || wingenemy_animation[1] == -1)
	{
		throw("�n�l�e�L�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	boxenemy_image = boxenemy_animation[0];
	wingenemy_image = wingenemy_animation[0];

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, 0.0f);


}

//�X�V����
void Enemy::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Enemy::Draw() const
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

	//�������ƂɃn�R�e�L�摜��`��
	DrawRotaGraphF(location.x, location.y, 0.8, radian, boxenemy_image, TRUE, flip_flag);
	DrawRotaGraphF(location.x, location.y, 0.8, radian, wingenemy_image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();
}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(boxenemy_animation[0]);
	DeleteGraph(boxenemy_animation[1]);
	DeleteGraph(wingenemy_animation[0]);
	DeleteGraph(wingenemy_animation[1]);
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	direction = 0.0f;
}

//�ړ�����
void Enemy::Movement()
{
	//��ʒ[�ɓ��B������A�i�s�����𔽓]������
	if (((location.x + direction.x) < box_size.x) ||
		(940.0f - box_size.x) < (location.x + direction.x))
	{
		direction.x *= -1.0f;
	}

	if (((location.y + direction.y) < box_size.y) ||
		(580.0f - box_size.y) < (location.y + direction.y))
	{
		direction.y *= -1.0f;
	}
   
	//�i�s�����Ɍ������āA�ʒu���W��ύX����
	location += direction;
}


//�A�j���[�V��������
void Enemy::AnimationControl()
{
	//�A�j���[�V�����J�E���g���v�Z����
	animation_count++;

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�����Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (boxenemy_image == boxenemy_animation[0])
		{
			boxenemy_image = boxenemy_animation[1];
		}
		else
		{
			boxenemy_image = boxenemy_animation[0];
		}

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