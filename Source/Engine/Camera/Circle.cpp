//#include <tge/engine.h>
//
//#include "Circle.h"
//#include "CommonUtilities/InputManager.h"
//
//Circle::Circle(const CommonUtilities::Vector3f& aPosition, eShape aShape)
//	: myRotateSpeed(30.0f)
//	, myPi(3.14159265358979323846f)
//{
//	auto& engine = *Tga::Engine::GetInstance();
//	myResolution = { static_cast<float>(engine.GetRenderSize().x), static_cast<float>(engine.GetRenderSize().y) };
//
//	int radial = 0;
//	int tubular = 0;
//	float thickness = 0;
//	float radius = 0;
//
//	switch (aShape)
//	{
//	case eShape::Donut:
//		radial = 15;
//		tubular = 20;
//		thickness = 0.1f;
//		radius = 0.5f;
//		break;
//	case eShape::Sphere:
//		radial = 15;
//		tubular = 20;
//		thickness = 0.8f;
//		radius = 0.0f;
//		break;
//	default:
//		break;
//	}
//
//	for (float i = 0; i < radial; ++i)
//	{
//		for (float j = 0; j < tubular; ++j)
//		{
//			float x, y, z, u, v;
//
//			u = j / tubular * myPi * 2.f;
//			v = i / radial * myPi * 2.f;
//
//			x = (radius + thickness * cosf(v)) * cosf(u);
//			y = (radius + thickness * cosf(v)) * sinf(u);
//			z = thickness * sinf(v);
//
//			myDonutCorners.push_back({ x,y,z,1 });
//			myRotatedDonutCorners.push_back({ x,y,z,1 });
//		}
//	}
//
//	myModelToWorldTransform(4, 1) = aPosition.x;
//	myModelToWorldTransform(4, 2) = aPosition.y;
//	myModelToWorldTransform(4, 3) = aPosition.z;
//}
//
//void Circle::Update(const float aTimeDelta)
//{
//	if (CommonUtilities::InputManager::GetInstance().GetAKeyIsPressed())
//	{
//		CommonUtilities::Vector3f currentPosition(myModelToWorldTransform(4, 1), myModelToWorldTransform(4, 2), myModelToWorldTransform(4, 3));
//
//		myModelToWorldTransform(4, 1) = 0;
//		myModelToWorldTransform(4, 2) = 0;
//		myModelToWorldTransform(4, 3) = 0;
//
//		if (CommonUtilities::InputManager::GetInstance().IsHold(VK_SHIFT))
//		{
//			myRotateSpeed = -(std::abs(myRotateSpeed));
//		}
//		else
//		{
//			myRotateSpeed = std::abs(myRotateSpeed);
//		}
//
//		if (CommonUtilities::InputManager::GetInstance().IsHold('Y'))
//		{
//			myModelToWorldTransform *= CommonUtilities::Matrix4x4f::CreateRotationAroundX(myRotateSpeed * myPi / 180.f * aTimeDelta);
//		}
//
//		if (CommonUtilities::InputManager::GetInstance().IsHold('H'))
//		{
//			myModelToWorldTransform *= CommonUtilities::Matrix4x4f::CreateRotationAroundY(myRotateSpeed * myPi / 180.f * aTimeDelta);
//		}
//
//		if (CommonUtilities::InputManager::GetInstance().IsHold('N'))
//		{
//			myModelToWorldTransform *= CommonUtilities::Matrix4x4f::CreateRotationAroundZ(myRotateSpeed * myPi / 180.f * aTimeDelta);
//		}
//
//		myModelToWorldTransform(4, 1) = currentPosition.x;
//		myModelToWorldTransform(4, 2) = currentPosition.y;
//		myModelToWorldTransform(4, 3) = currentPosition.z;
//	}
//}
//
//void Circle::Render(Tga::DebugDrawer& aDbg, Camera2& aCamera)
//{
//	for (int i = 0; i < myDonutCorners.size(); i++)
//	{
//		myRotatedDonutCorners[i] = myDonutCorners[i] * myModelToWorldTransform;
//		myRotatedDonutCorners[i] = aCamera.WorldToCameraSpace(myRotatedDonutCorners[i]);
//		myRotatedDonutCorners[i] = aCamera.CameraToProjectionSpace(myRotatedDonutCorners[i]);
//	}
//
//	for (int i = 0; i < myDonutCorners.size(); i++)
//	{
//		myRotatedDonutCorners[i].x = aCamera.ProjectionToPixel(myRotatedDonutCorners[i]).x;
//		myRotatedDonutCorners[i].y = aCamera.ProjectionToPixel(myRotatedDonutCorners[i]).y;
//
//		if (myRotatedDonutCorners[i].z > aCamera.GetNearPlane() && myRotatedDonutCorners[i].z < aCamera.GetFarPlane())
//		{
//			aDbg.DrawCircle({ myRotatedDonutCorners[i].x, myRotatedDonutCorners[i].y }, 2.0f);
//		}
//	}
//}
