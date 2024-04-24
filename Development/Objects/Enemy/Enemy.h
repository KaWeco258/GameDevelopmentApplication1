#pragma once

#include "../../Utility/Vector2D.h"

//�Q�[���I�u�W�F�N�g���N���X
class Enemy
{
protected:
	Vector2D location;     //�ʒu���
	double scale;          //�傫��
	double radian;         //����
	int image;             //�`�悷��摜
	int sound;             //�Đ����鉹��

private:
	int animation[2];      //�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V��������
	int flip_flag;         //���]�t���O


public:
	Enemy();                  //�R���X�g���N�^
	virtual ~Enemy();         //�f�X�g���N�^

	virtual void Initialize();     //����������
	virtual void Update();         //�X�V����
	virtual void Draw() const;     //�`�揈��
	virtual void Finalize();       //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(Enemy* hit_object);

	

private:
	//�A�j���[�V��������
	void AnimationControl();

};