#pragma once

namespace SimpleTracker
{
	struct MemoryTrackingSettings
	{
		bool myShouldStoreStackTraces;
		bool myShouldTrackAllAllocations;
	};

	void StartMemoryTracking(const MemoryTrackingSettings& trackingSettings);
	void StopMemoryTrackingAndPrint();
}