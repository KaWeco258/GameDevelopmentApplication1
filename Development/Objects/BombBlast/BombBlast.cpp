#include "BombBlast.h"
#include "DxLib.h"
#include "../BoxEnemy/BoxEnemy.h"
#include "../Bomb/Bomb.h"

//�R���X�g���N�^
BombBlast::BombBlast() : animation_count(0), direction(0.0f),box_size(0.0),radian(0.0), blast_image(0)
{
	blast_animation[0] = NULL;
	blast_animation[1] = NULL;
	blast_animation[2] = NULL;
}

//�f�X�g���N�^
BombBlast::~BombBlast()
{

}

//����������
void BombBlast::Initialize()
{
	//�摜�̓ǂݍ���
	//bomb_animation = LoadGraph("Resource/Images/Bomb/Bomb.png");
	blast_animation[0] = LoadGraph("Resource/Images/Blast/1.png");
	blast_animation[1] = LoadGraph("Resource/Images/Blast/2.png");
	blast_animation[2] = LoadGraph("Resource/Images/Blast/3.png");
	

	//�G���[�`�F�b�N
	/*if (bomb_animation == -1)
	{
		throw("���e�̉摜������܂���\n");
	}*/

	if (blast_animation[0] == -1 || blast_animation[1] == -1 || blast_animation[2] == -1)
	{
		throw("�����̉摜������܂���\n");
	}

	//�����̐ݒ�
	radian = 0.0f;

	//�����蔻��̑傫����ݒ�
	box_size = 64.0f;

	//�����摜�̐ݒ�
	//bomb_image = bomb_animation;
	blast_image = blast_animation[0];
	

	//�����i�s�����̐ݒ�
	direction = Vector2D(1.0f, -0.5f);


}

//�X�V����
void BombBlast::Update()
{
	//�ړ�����
	//Movement();
	//�A�j���[�V��������
	AnimationControl();
}

//�`�揈��
void BombBlast::Draw() const
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

	//�������Ƃɔ��e�摜��`��
	//DrawRotaGraphF(location.x, location.y, 0.8, radian, bomb_image, TRUE, flip_flag);                
	DrawRotaGraphF(location.x, location.y, 0.8, radian, blast_image, TRUE, flip_flag);

	//�e�N���X�̕`�揈�����Ăяo��
	//__super::Draw();

	//�f�o�b�O�p
//#if _DEBUG
//	//�����蔻��̉���
//	Vector2D box_collision_upper_left = location - (box_size / 2.0f);
//	Vector2D box_collision_lower_right = location + (box_size / 2.0f);
//
//	DrawBoxAA(box_collision_upper_left.x, box_collision_upper_left.y,
//		box_collision_lower_right.x, box_collision_lower_right.y,
//		GetColor(255, 0, 0), FALSE);
//#endif	   
}

//�I��������
void BombBlast::Finalize()
{
	//�g�p�����摜�����
	//DeleteGraph(bomb_animation);
	DeleteGraph(blast_animation[0]);
	DeleteGraph(blast_animation[1]);
	DeleteGraph(blast_animation[2]);
}



//�ړ�����
//void BombBlast::Movement()
//{
//	
//	//��ԉ��܂Ŕ��e�𗎂Ƃ�
//	if (((location.y + direction.y) < box_size.y) ||
//		(580.0f - box_size.y) < (location.y + direction.y))
//	{
//		direction.x = 0.0f;
//		direction.y *= 1.1f;
//	}
//
//	//���݂̈ʒu���W�ɑ��������Z����
//	location -= direction;
//
//
//	
//
//}
//

//�����蔻��ʒm����
void BombBlast::OnHitCollision(GameObject* hit_object)
{
	//�����������ɍs������
	
	//���e�ɓ������Ė���������
	//if (dynamic_cast<Bomb*>(hit_object) != nullptr)
	//{
	//	//�G��`�悵������
	//	Efface = TRUE;
	//}
	////���e�ɓ���������
	//else
	//{
	//	//�G����������
	//	Efface = FALSE;
	//	//�A�j���[�V��������
	//	
	//}
	//AnimationControl();
}

//�A�j���[�V��������
void BombBlast::AnimationControl()
{
	//�A�j���[�V�����J�E���g���v�Z����
	animation_count++;
	
	

	//30�t���[���ڂɓ��B������
	if (animation_count >= 30)
	{
		//�J�E���g�����Z�b�g
		animation_count = 0;

		/*if(Efface==FALSE)
		{*/
			//NULL�������̂��A�j���[�V�����ɕϊ�������
		//	blast_image = blast_animation[0];
			
			//�摜�̐؂�ւ�
			if (blast_image == blast_animation[0])
			{
				blast_image = blast_animation[1];
			}
			else if (blast_image == blast_animation[1])
			{
				blast_image = blast_animation[2];
			}
			else if (blast_image == blast_animation[2])
			{
				blast_image = NULL;
			}
			
		/*}*/
	}
}