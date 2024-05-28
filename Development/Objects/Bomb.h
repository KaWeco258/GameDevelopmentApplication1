#pragma once

#include "../Utility/Vector2D.h"


//�Q�[���I�u�W�F�N�g���N���X
class Bomb

{
private:
	int animation_count;   //�A�j���[�V��������
	Vector2D direction;     //�i�s����
	int bomb_animation;             //�`�悷��摜
	double radian;         //����
	Vector2D location;     //�ʒu���
	Vector2D box_size;          //�傫��
	int bomb_image;             //�`�悷��摜


public:
	Bomb();                  //�R���X�g���N�^
	~Bomb();                 //�f�X�g���N�^

	virtual void Initialize();     //����������
	virtual void Update();         //�X�V����
	virtual void Draw() const;     //�`�揈��
	virtual void Finalize();       //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(Bomb* hit_object);



private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	//void AnimationControl();

	
};