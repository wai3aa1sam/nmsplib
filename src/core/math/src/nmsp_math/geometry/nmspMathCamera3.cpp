#include "nmsp_math-pch.h"
#include "nmspMathCamera3.h"

namespace nmsp {
namespace math {

#if 0
#pragma mark --- Camera3_T-Impl ---
#endif // 0
#if 1

template<class T>
Camera3_T<T>::Camera3_T()
{
	//setUp(Vec3::s_down());
}

template<class T>
Camera3_T<T>::~Camera3_T()
{

}

template<class T>
void Camera3_T<T>::pan(T x, T y) {
	auto v = _aim - _pos;
	auto right = _up.cross(v).normalize();

	auto q = Quat4::s_eulerY(x) * Quat4::s_angleAxis(y, right);
	v    = q * v;
	_up  = q * _up;
	_aim = _pos + v;
}

template<class T>
void Camera3_T<T>::orbit(T x, T y) {
	auto v = _pos - _aim;
	auto right = _up.cross(v).normalize();

	auto q = Quat4::s_angleAxis(y, right) * Quat4::s_eulerY(x);
	v    = q * v;
	_up  = q * _up;
	_pos = _aim + v;
}

template<class T>
void Camera3_T<T>::move(T x, T y, T z) {
	auto v = _aim - _pos;
	auto dir = v.normalize();
	auto right = _up.cross(dir);

	auto t = right * x + _up * y + dir * z;
	_pos += t;
	_aim += t;
}

template<class T>
void Camera3_T<T>::dolly(T z) 
{
	auto v = _pos - _aim;
	auto dir = v.normalize();
	auto d = v.magnitude();
	d += z;
	d = math::max(d, sCast<T>(0.001));

	_pos = _aim + dir * d;
}

template<class T>
typename Camera3_T<T>::Ray3 Camera3_T<T>::getRay(const Vec2& screenPos) const {
	return Ray3::s_unprojectFromInvMatrix(screenPos, viewProjMatrix().inverse(), _viewport);
}

template<class T>
void 
Camera3_T<T>::setPerspective()
{
	_orthoScale = invalidOrthographicScale();
}

template<class T>
void 
Camera3_T<T>::setOrthographic(const T& orthoScale)
{
	_orthoScale = orthoScale;
}

template<class T>
typename Camera3_T<T>::Mat4 Camera3_T<T>::viewMatrix() const {
	return Mat4::s_lookAt(_pos, _aim, _up);
}

template<class T>
typename Camera3_T<T>::Mat4 Camera3_T<T>::projMatrix() const {
	T aspect = aspectRatio();
	auto n = 1.0 * _orthoScale;

	//auto matrix = Mat4::s_perspective(math::radians(_fov), aspect, _nearClip, _farClip);		// perspectiveFovRH_NO
	auto matrix = isOrthgraphicMode() ?
		glm::orthoRH_ZO(T(-n) * aspect, T(n) * aspect, T(-n), T(n), _nearClip, _farClip)
		: glm::perspectiveRH_ZO(math::radians(_fov), aspect, _nearClip, _farClip);

	//matrix		= glm::orthoRH_ZO(T(_viewport.x), T(_viewport.x + _viewport.w), T(_viewport.y), T(_viewport.y + _viewport.h), _nearClip, _farClip);
	//matrix		= glm::ortho(T(0.0), T(_viewport.w), T(0.0), T(_viewport.h), _nearClip, _farClip);

	return matrix;
}

template struct Camera3_T<float>;
template struct Camera3_T<double>;

#endif

}
}