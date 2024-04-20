#pragma once

//�Q�����x�N�g���N���X
class Vector2D
{
public:
	//X���W
	float x;
	//Y���W
	float y;

public:
	//�R���X�g���N�^
	Vector2D();
	Vector2D(float scalar);
	Vector2D(float mx, float my);
	//�f�X�g���N�^
	~Vector2D();

public:

	//���Z�q�I�[�o�[���[�h
	//������Z
	Vector2D& operator=(const Vector2D& location);

	//���Z
	const Vector2D operator + (const Vector2D& location) const;
	Vector2D& operator += (const Vector2D& location);

	//���Z
	const Vector2D operator - (const Vector2D& location) const;
	Vector2D& operator -= (const Vector2D& location);

	//��Z
	const Vector2D operator * (const float& scalar) const;
	const Vector2D operator * (const Vector2D& location) const;
	Vector2D& operator *= (const float& scalar);
	Vector2D& operator *= (const Vector2D& location);

	//���Z
	const Vector2D operator / (const float& scalar) const;
	const Vector2D operator / (const Vector2D& location) const;
	Vector2D& operator /= (const float& scalar);
	Vector2D& operator /= (const Vector2D& location);

	//�����^�֕ϊ�
	void ToInt(int* x, int* y)const;
};