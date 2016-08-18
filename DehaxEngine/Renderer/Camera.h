#pragma once
#include "..\stdafx.h"

#include <cmath>

class DEHAXENGINE_API Camera {
public:
	enum ProjectionType { Parallel, Perspective };

	Camera();
	Camera(const DirectX::XMFLOAT3 &position, const DirectX::XMFLOAT3 &lookAt, const DirectX::XMFLOAT3 &up, float FOV = DirectX::XM_PIDIV2);

	void Rotate(const float &angleX, const float &angleY, const float &angleZ);
	void Zoom(const float &multiplier);
	void ChangeProjection();
	void Move(const DirectX::XMFLOAT3 &offset);
	/*void StrafeRight(const float &value);
	void StrafeForward(const float &value);
	void StrafeUp(const float &value);*/

	int getWidth() const;
	void setWidth(const int &width);
	int getHeight() const;
	void setHeight(const int &height);
	float getZoom() const;
	void setZoom(const float &zoom);
	ProjectionType getProjection() const;
	void setProjection(const ProjectionType &projection);
	DirectX::XMFLOAT3 getPosition() const;
	void setPosition(const DirectX::XMFLOAT3 &position);
	DirectX::XMFLOAT3 getLookAt() const;
	void setLookAt(const DirectX::XMFLOAT3 &lookAt);
	DirectX::XMFLOAT3 getUp() const;
	void setUp(const DirectX::XMFLOAT3 &up);
	float getFOV() const;
	void setFOV(const float &FOV);
	float getNearZ();
	void setNearZ(const float &nearZ);
	float getFarZ();
	void setFarZ(const float &farZ);
	float getViewDistance() const;
	void setViewDistance(float d);

private:
	const ProjectionType DEFAULT_PROJECTION = Perspective;
	const DirectX::XMFLOAT3 DEFAULT_POSITION = DirectX::XMFLOAT3(0.0f, 0.0f, -10.0f);
	const DirectX::XMFLOAT3 DEFAULT_LOOK_AT = DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f);
	const DirectX::XMFLOAT3 DEFAULT_UP = DirectX::XMFLOAT3(0.0f, 1.0f, 0.0f);
	const float DEFAULT_FOV = DirectX::XM_PIDIV2;
	const float MIN_FOV = 20.0f;
	const float MAX_FOV = 150.0f;
	const float DEFAULT_PARALLEL_ZOOM = 500.0f;
	const float DEFAULT_NEAR_Z = 0.01f;
	const float DEFAULT_FAR_Z = 100.0f;

	int m_width;
	int m_height;
	float m_zoom;

	ProjectionType m_projection;
	DirectX::XMFLOAT3 m_position;
	DirectX::XMFLOAT3 m_lookAt;
	DirectX::XMFLOAT3 m_up;
	float m_fov;
	float m_nearPlaneZ;
	float m_farPlaneZ;

	float m_theta;
	float m_phi;
};
