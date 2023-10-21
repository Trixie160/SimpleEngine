#include "global.h"
#include "engine.h"

namespace
{
	Engine* globalEngine = nullptr;
}

void SimplyGlobalImpl::SetEngine(Engine* aEngine)
{
	globalEngine = aEngine;
}

double SimplyGlobal::GetTotalTime()
{
	return globalEngine->GetTotalTime();
}

float SimplyGlobal::GetDeltaTime()
{
	return globalEngine->GetDeltaTime();
}

