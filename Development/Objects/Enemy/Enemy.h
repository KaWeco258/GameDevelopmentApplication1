#pragma once

#include "../GameObject.h"
#include "../../Utility/Vector2D.h"

//�Q�[���I�u�W�F�N�g���N���X
class Enemy : public GameObject
{
private:
	int animation[2];      //�A�j���[�V�����摜
	int animation_count;   //�A�j���[�V��������
	int flip_flag;         //���]�t���O


public:
	Enemy();                  //�R���X�g���N�^
	virtual ~Enemy();         //�f�X�g���N�^

	virtual void Initialize() override;     //����������
	virtual void Update() override;         //�X�V����
	virtual void Draw() const override;     //�`�揈��
	virtual void Finalize() override;       //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object) override;

	

private:
	//�A�j���[�V��������
	void AnimationControl();

};