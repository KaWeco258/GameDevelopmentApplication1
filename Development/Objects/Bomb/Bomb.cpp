#include "Bomb.h"
#include "DxLib.h"
#include "../Enemy/BoxEnemy.h"

//�R���X�g���N�^
Bomb::Bomb() : animation_count(0), direction(0.0f),box_size(0.0),radian(0.0), bomb_image(0)
{
	bomb_animation = NULL;
}

//�f�X�g���N�^
Bomb::~Bomb()
{

}

//����������
void Bomb::Initialize()
{
	//�摜�̓ǂݍ���
	bomb_animation = LoadGraph("Resource/Images/Bomb/Bomb.png");
	

	//�G���[�`�F�b�N
	if (bomb_animation == -1)
	{
		throw("���e�̉摜������܂���\n");
	}
	
	

	//�����̐ݒ�
	radian = -1.6f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	bomb_image = bomb_animation;
	

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, -0.5f);


}

//�X�V����
void Bomb::Update()
{
	//�ړ�����
	Movement();
	//�A�j���[�V��������
	//AnimationControl();
}

//�`�揈��
void Bomb::Draw() const
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
	DrawRotaGraphF(location.x, location.y, 0.8, radian, bomb_image, TRUE, flip_flag);                

	//�e�N���X�̕`�揈�����Ăяo��
	__super::Draw();

	//�f�o�b�O�p
#if _DEBUG
	//�����蔻��̉���
	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
	Vector2D box_collision_lower_right = location + (box_size / 2.0f);

	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
		box_collision_lower_right.x, box_collision_lower_right.y,
		GetColor(255, 0, 0), FALSE);
#endif	   
}

//�I��������
void Bomb::Finalize()
{
	//�g�p�����摜�����
	DeleteGraph(bomb_animation);
	
}



//�ړ�����
void Bomb::Movement()
{
	
	//��ԉ��܂Ŕ��e�𗎂Ƃ�
	if (((location.y + direction.y) < box_size.y) ||
		(580.0f - box_size.y) < (location.y + direction.y))
	{
		direction.x = 0.0f;
		direction.y *= 1.1f;
	}

	//���݂̈ʒu���W�ɑ��������Z����
	location -= direction;


	

}

//�����蔻��ʒm����
void Bomb::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	
	//���e�ɓ������Ė���������
	if (dynamic_cast<BoxEnemy*>(hit_object) != nullptr)
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

////�A�j���[�V��������
//void Bomb::AnimationControl()
//{
//	//�A�j���[�V�����J�E���g���v�Z����
//	animation_count++;
//
//	//30�t���[���ڂɓ��B������
//	if (animation_count >= 30)
//	{
//		//�J�E���g�����Z�b�g
//		animation_count = 0;
//
//		//�摜�̐؂�ւ�
//		if (boxenemy_image == boxenemy_animation[0])
//		{
//			boxenemy_image = boxenemy_animation[1];
//		}
//		else
//		{
//			boxenemy_image = boxenemy_animation[0];
//		}
//
//		if (wingenemy_image == wingenemy_animation[0])
//		{
//			wingenemy_image = wingenemy_animation[1];
//		}
//		else
//		{
//			wingenemy_image = wingenemy_animation[0];
//		}
//	}
//}