#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER  //���W�̒��_���摜�̒��S�ɂ���


//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;			//�ʒu���
	Vector2D box_size;          //�傫��
	double radian;				//����
	int boxenemy_image;         //�`�悷��摜(���G)
	int wingenemy_image;        //�`�悷��摜(�H�G)
	//int blast_image[3];        //�`�悷��摜(����)
	int player_image;           //�`�悷��摜(�v���C���[)
	int sound;					//�Đ����鉹��
	bool Efface;          //��������(��)



public:
	GameObject();                  //�R���X�g���N�^
	virtual ~GameObject();         //�f�X�g���N�^

	virtual void Initialize();     //����������
	virtual void Update();         //�X�V����
	virtual void Draw() const;     //�`�揈��
	virtual void Finalize();       //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//��������(��)
	bool EffaceObjects();

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;
};