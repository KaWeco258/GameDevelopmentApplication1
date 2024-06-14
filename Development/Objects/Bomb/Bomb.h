#pragma once


#include "../GameObject.h"

//�Q�[���I�u�W�F�N�g���N���X
class Bomb : public GameObject

{
private:
	int animation_count;      //�A�j���[�V��������
	Vector2D direction;       //�i�s����
	int bomb_animation;       //�`�悷��摜
	double radian;            //����

	Vector2D box_size;        //�傫��
	int bomb_image;           //�`�悷��摜


public:
	Bomb();                  //�R���X�g���N�^
	~Bomb();                 //�f�X�g���N�^

	virtual void Initialize() override;     //����������
	virtual void Update() override;         //�X�V����
	virtual void Draw() const override;     //�`�揈��
	virtual void Finalize() override;       //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(Bomb* hit_object);



private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	//void AnimationControl();

	
};