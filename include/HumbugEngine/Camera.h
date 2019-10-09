#pragma once
#include "HumbugEngine/Vector.h"

class Camera {
public:
	Camera();

	void SetSize(int w, int h);

	Matrix4 InverseProjection() const;

	Matrix4 Matrix() const;

	void UsePerspectiveMatrix(float n, float f);
	void UseOrthoMatrix(float left, float right, float bottom, float top, float n, float f);
	void SetPositionOrientation(const Vector3& pos, float rotX, float rotY);

	void UseViewport() const;

	void ClipOblique(const Vector3& pos, const Vector3& normal);

	Matrix4 projection;
	Matrix4 worldView;

	int width;
	int height;
	float near;
	float far;
};
