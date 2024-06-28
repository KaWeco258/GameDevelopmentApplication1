#pragma once

#include "../Utility/Vector2D.h"

#define D_PIVOT_CENTER  //���W�̒��_���摜�̒��S�ɂ���

#define PLAYER	(0)
#define ENEMY	(1)
#define BOMB	(2)
#define	EFFECT	(3)


//�Q�[���I�u�W�F�N�g���N���X
class GameObject
{
protected:
	Vector2D location;			//�ʒu���
	Vector2D box_size;          //�傫��
	double radian;				//����
	int boxenemy_image;         //�`�悷��摜(���G)
	int wingenemy_image;        //�`�悷��摜(�H�G)
	int goldenemy_image;        //�`�悷��摜(���G)
	int harpy_image;        //�`�悷��摜(���G)
	int player_image;           //�`�悷��摜(�v���C���[)
	int sound;					//�Đ����鉹��
	bool Efface;          //��������(��)
	int type;				//�I�u�W�F�N�g�̃^�C�v
	int score;				//�I�u�W�F�N�g�̃^�C�v

public:
	float speed;


public:
	GameObject();                  //�R���X�g���N�^
	virtual ~GameObject();         //�f�X�g���N�^

	virtual void Initialize();     //����������
	virtual void Update();         //�X�V����
	virtual void Draw() const;     //�`�揈��
	virtual void Finalize();       //�I��������

	//�����蔻��ʒm����
	virtual void OnHitCollision(GameObject* hit_object);

	//��������
	bool EffaceObjects();

	//�I�u�W�F�N�g�̃^�C�v�擾
	int GetObjectType();

	//�ʒu���擾����
	Vector2D GetLocation() const;
	//
	int GetScore(); //const;
	//�ʒu���ύX����
	void SetLocation(const Vector2D& location);

	//�����蔻��̑傫�����擾����
	Vector2D GetBoxSize() const;
	
	//�A�j���[�V��������
	void AnimationControl();
};