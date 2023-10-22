#pragma once

class Engine;

class SimplyGlobalImpl
{
	friend class Engine;
	SimplyGlobalImpl();
	static void SetEngine(Engine* aEngine);
};

namespace SimplyGlobal
{
	double GetTotalTime();
	float GetDeltaTime();
}
