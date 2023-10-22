//#pragma once
//#include "../Engine/tge/drawers/DebugDrawer.h"
//#include <vector>
//
//#include "Camera2.h"
//#include "Vector.h"
//
//enum class eShape
//{
//	Donut,
//	Sphere
//};
//
//class Circle
//{
//public:
//	Circle(const CommonUtilities::Vector3f& aPosition, eShape aShape = eShape::Donut);
//	~Circle() = default;
//
//
//	void Update(const float aTimeDelta);
//	void Render(Tga::DebugDrawer& aDbg, Camera2& aCamera);
//private:
//	CommonUtilities::Matrix4x4f myModelToWorldTransform;
//
//	std::vector<CommonUtilities::Vector4f> myDonutCorners;
//	std::vector<CommonUtilities::Vector4f> myRotatedDonutCorners;
//
//	CommonUtilities::Vector2f myResolution;
//
//	float myRotateSpeed;
//	const float myPi;
//};