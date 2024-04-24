#pragma once

#include "../Utility/Vector2D.h"

//�Q�[���I�u�W�F�N�g���N���X
class GameObject
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
	GameObject();                  //�R���X�g���N�^
	virtual ~GameObject();         //�f�X�g���N�^

	virtual void Initialize();     //����������
	virtual void Update();         //�X�V����
	virtual void Draw() const;     //�`�揈��
	virtual void Finalize();       //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

private:
	//�A�j���[�V��������
	void AnimationControl();

};