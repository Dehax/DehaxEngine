#include "..\stdafx.h"
#include "Camera.h"

#include <limits>

Camera::Camera()
{
	m_position = DEFAULT_POSITION;
	m_lookAt = DEFAULT_LOOK_AT;
	m_up = DEFAULT_UP;
	m_fov = DEFAULT_FOV;
	m_projection = DEFAULT_PROJECTION;
	m_zoom = DEFAULT_PARALLEL_ZOOM;
	m_nearPlaneZ = DEFAULT_NEAR_Z;
	m_farPlaneZ = DEFAULT_FAR_Z;

	m_theta = DirectX::XM_PIDIV2;
	m_phi = 0.0f;
}

Camera::Camera(const DirectX::XMFLOAT3 &position, const DirectX::XMFLOAT3 &lookAt, const DirectX::XMFLOAT3 &up, float FOV)
{
	m_position = position;
	m_lookAt = lookAt;
	m_up = up;
	m_fov = FOV;
	m_projection = DEFAULT_PROJECTION;
	m_zoom = DEFAULT_PARALLEL_ZOOM;
	m_nearPlaneZ = DEFAULT_NEAR_Z;
	m_farPlaneZ = DEFAULT_FAR_Z;

	m_theta = DirectX::XM_PIDIV2;
	m_phi = 0.0f;
}

void Camera::Rotate(const float &angleX, const float &angleY, const float &angleZ)
{
	// TODO: Добавить поворот камеры по Z (UP-vector).
	DirectX::XMVECTOR oldPosition = DirectX::XMVectorSubtract(DirectX::XMLoadFloat3(&m_position), DirectX::XMLoadFloat3(&m_lookAt));

	float r = DirectX::XMVector3Length(oldPosition).m128_f32[0];

	float thetaDeg = DirectX::XMConvertToDegrees(m_theta);

	if (angleX < 0.0f && thetaDeg + angleX >= 5.0f) {
		m_theta += angleX;
	}
	else if (angleX > 0.0f && thetaDeg + angleX <= 175.0f) {
		m_theta += angleX;
	}

	m_phi += angleY;

	DirectX::XMFLOAT3 newPosition = DirectX::XMFLOAT3(r * std::sin(m_theta) * std::sin(m_phi), r * std::cos(m_theta), -r * std::sin(m_theta) * std::cos(m_phi));

	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&newPosition), DirectX::XMLoadFloat3(&m_lookAt)));
}

void Camera::RotateAround(const float &angleX, const float &angleY, const float &angleZ)
{
	
}

void Camera::Zoom(const float &multiplier)
{
	if (std::abs(multiplier) < 0.000001f) {
		return;
	}

	float zoom = std::pow(2.0f, multiplier);

	switch (m_projection) {
	case Parallel:
		m_zoom *= zoom;
		break;
	case Perspective:
		float newFOV = m_fov - multiplier * DirectX::XMConvertToRadians(1.0f);
		setFOV(newFOV);
		break;
	}
}

void Camera::ChangeProjection()
{
	if (m_projection == Perspective) {
		m_projection = Parallel;
	}
	else if (m_projection == Parallel) {
		m_projection = Perspective;
	}
}

void Camera::Move(const DirectX::XMFLOAT3 &offset)
{
	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&m_position), DirectX::XMLoadFloat3(&offset)));
	DirectX::XMStoreFloat3(&m_lookAt, DirectX::XMVectorAdd(DirectX::XMLoadFloat3(&m_lookAt), DirectX::XMLoadFloat3(&offset)));
}

void Camera::StrafeRight(const float &value)
{
	DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
	DirectX::XMVECTOR lookAt = DirectX::XMLoadFloat3(&m_lookAt);

	DirectX::XMVECTOR zAxis = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(lookAt, position));
	DirectX::XMVECTOR xAxis = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&m_up), zAxis));
	DirectX::XMVECTOR delta = DirectX::XMVectorScale(xAxis, value);

	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(position, delta));
	DirectX::XMStoreFloat3(&m_lookAt, DirectX::XMVectorAdd(lookAt, delta));
}

void Camera::StrafeForward(const float &value)
{
	DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
	DirectX::XMVECTOR lookAt = DirectX::XMLoadFloat3(&m_lookAt);

	DirectX::XMVECTOR zAxis = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(lookAt, position));
	DirectX::XMVECTOR delta = DirectX::XMVectorScale(zAxis, value);

	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(position, delta));
	DirectX::XMStoreFloat3(&m_lookAt, DirectX::XMVectorAdd(lookAt, delta));
}

void Camera::StrafeUp(const float &value)
{
	DirectX::XMVECTOR position = DirectX::XMLoadFloat3(&m_position);
	DirectX::XMVECTOR lookAt = DirectX::XMLoadFloat3(&m_lookAt);

	DirectX::XMVECTOR zAxis = DirectX::XMVector3Normalize(DirectX::XMVectorSubtract(lookAt, position));
	DirectX::XMVECTOR xAxis = DirectX::XMVector3Normalize(DirectX::XMVector3Cross(zAxis, DirectX::XMLoadFloat3(&m_up)));
	DirectX::XMVECTOR yAxis = DirectX::XMVector3Cross(xAxis, zAxis);
	DirectX::XMVECTOR delta = DirectX::XMVectorScale(yAxis, value);

	DirectX::XMStoreFloat3(&m_position, DirectX::XMVectorAdd(position, delta));
	DirectX::XMStoreFloat3(&m_lookAt, DirectX::XMVectorAdd(lookAt, delta));
}

float Camera::getViewDistance() const
{
	return m_width / (2 * std::tan(m_fov / 2.0f));
}

void Camera::setViewDistance(float d)
{
	m_fov = 2 * std::atan(0.5f * m_width / d);
}

float Camera::getFOV() const
{
	return m_fov;
}

void Camera::setFOV(const float &FOV)
{
	if (FOV <= DirectX::XMConvertToRadians(MAX_FOV) && FOV >= DirectX::XMConvertToRadians(MIN_FOV)) {
		m_fov = FOV;
	}
}

float Camera::getNearZ()
{
	return m_nearPlaneZ;
}

void Camera::setNearZ(const float &nearZ)
{
	if (nearZ >= 1.0f && nearZ < m_farPlaneZ) {
		m_nearPlaneZ = nearZ;
	}
}

float Camera::getFarZ()
{
	return m_farPlaneZ;
}

void Camera::setFarZ(const float & farZ)
{
	if (farZ <= 1000.0f && farZ > m_nearPlaneZ) {
		m_farPlaneZ = farZ;
	}
}

int Camera::getWidth() const
{
	return m_width;
}

void Camera::setWidth(const int &width)
{
	m_width = width;
}

int Camera::getHeight() const
{
	return m_height;
}

void Camera::setHeight(const int &height)
{
	m_height = height;
}

float Camera::getZoom() const
{
	return m_zoom;
}

void Camera::setZoom(const float &zoom)
{
	m_zoom = zoom;
}

Camera::ProjectionType Camera::getProjection() const
{
	return m_projection;
}

void Camera::setProjection(const ProjectionType &projection)
{
	m_projection = projection;
}

DirectX::XMFLOAT3 Camera::getPosition() const
{
	return m_position;
}

void Camera::setPosition(const DirectX::XMFLOAT3 &position)
{
	m_position = position;
}

DirectX::XMFLOAT3 Camera::getLookAt() const
{
	return m_lookAt;
}

void Camera::setLookAt(const DirectX::XMFLOAT3 &lookAt)
{
	m_lookAt = lookAt;
}

DirectX::XMFLOAT3 Camera::getUp() const
{
	return m_up;
}

void Camera::setUp(const DirectX::XMFLOAT3 &up)
{
	m_up = up;
}
