#pragma once

#include "../GameObject.h"

class Player
{
private:
	//�ʒu���
    int animation[2];
	//�i�s�������
	Vector2D direction;
	//���a
	float radius;

public:
	//�R���X�g���N�^
	Player();
	Player(float x, float y);
	Player(Vector2D location);
	//�f�X�g���N�^
	~Player();

	//�X�V����
	void Update();
	//�`�揈���iconst�����o�֐��j
	void Draw() const;

	//�ʒu���ݒ�ifloat�ŃI�[�o�[���[�h�j
	void SetLocation(float x, float y);
	//�ʒu���ݒ�ivector2D�ŃI�[�o�[���[�h�j
	void SetLocation(Vector2D location);
	//�ʒu���iconst�����o�ɂ���j
	Vector2D GetLocation() const;
	//���a���̎擾
	float GetRadius();

private:
	//�ړ�����
	void Movement();
};