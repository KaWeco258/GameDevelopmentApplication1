#include "Enemy.h"
#include "../../Utility/InputControl.h"
#include "DxLib.h"

//�R���X�g���N�^
Enemy::Enemy() : animation_count(0),flip_flag(FALSE)
{
	animation[0] = NULL;
	animation[1] = NULL;

}

//�f�X�g���N�^
Enemy::~Enemy()
{

}

//����������
void Enemy::Initialize()
{
	//�摜�̓ǂݍ���
	animation[0] = LoadGraph("Resource/Images/WingEnemy/1.png");
	animation[1] = LoadGraph("Resource/Images/WingEnemy/2.png");

	//�G���[�`�F�b�N
	if (animation[0] == -1 || animation[1] == -1)
	{
		throw("WingEnemy�̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	scale = 64.0f;

	//�����摜�̐ݒ�
	image = animation[0];

	
}

//�X�V����
void Enemy::Update()
{
	location.x += 1.0f;

	//��ʍ��ŏ�������܂���ʉE���琶������
	if (location.x >= 640.0f)
	{
		location.x = 0.0f;
	}

	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void Enemy::Draw() const
{
	//�v���C���[�摜�̕`��
	DrawRotaGraphF(0.0, 0.0, 1.0, radian, image, TRUE, flip_flag);
}

//�I��������
void Enemy::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(animation[0]);
	DeleteGraph(animation[1]);
}

//�����蔻��ʒm����
void Enemy::OnHitCollision(Enemy* hit_object)
{
	//�����������ɍs������
}




//�A�j���[�V��������
void Enemy::AnimationControl()
{
	//�A�j���[�V�����J�E���g���v�Z����
	animation_count++;

	//60�t���[���ڂɓ��B������
	if (animation_count >= 60)
	{
		//�J�E���g�����Z�b�g
		animation_count = 0;

		//�摜�̐؂�ւ�
		if (image == animation[0])
		{
			image = animation[1];
		}
		else
		{
			image = animation[0];
		}
	}
}