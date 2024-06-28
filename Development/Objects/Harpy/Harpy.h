#pragma once

#include "../GameObject.h"


//�Q�[���I�u�W�F�N�g���N���X
class Harpy : public GameObject
{
private:
	int harpy_animation[2];      //�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V��������
	Vector2D direction;     //�i�s����
	int r;     //����


public:
	Harpy();                  //�R���X�g���N�^
	~Harpy();                 //�f�X�g���N�^

	virtual void Initialize() override;     //����������
	virtual void Update() override;         //�X�V����
	virtual void Draw() const override;     //�`�揈��
	virtual void Finalize() override;       //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	//�ړ������̐ݒ�
	Vector2D SetDirection(Vector2D& E_direction);

private:
	//�ړ�����
	void Movement();
	//�A�j���[�V��������
	void AnimationControl();

};
