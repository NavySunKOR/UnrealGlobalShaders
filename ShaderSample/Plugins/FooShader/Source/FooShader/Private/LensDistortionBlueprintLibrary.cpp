// Copyright Epic Games, Inc. All Rights Reserved.

#include "LensDistortionBlueprintLibrary.h"


PRAGMA_DISABLE_DEPRECATION_WARNINGS
ULensDistortionBlueprintLibrary::ULensDistortionBlueprintLibrary()
{ }


// static
void ULensDistortionBlueprintLibrary::GetUndistortOverscanFactor(
	const FFooDistortionCameraModel& CameraModel,
	float DistortedHorizontalFOV,
	float DistortedAspectRatio,
	float& UndistortOverscanFactor)
{
	UndistortOverscanFactor = CameraModel.GetUndistortOverscanFactor(DistortedHorizontalFOV, DistortedAspectRatio);
}


// static
void ULensDistortionBlueprintLibrary::DrawUVDisplacementToRenderTarget(
	const UObject* WorldContextObject,
	const FFooDistortionCameraModel& CameraModel,
	float DistortedHorizontalFOV,
	float DistortedAspectRatio,
	float UndistortOverscanFactor,
	class UTextureRenderTarget2D* OutputRenderTarget,
	float OutputMultiply,
	float OutputAdd)
{
	CameraModel.DrawUVDisplacementToRenderTarget(
		WorldContextObject->GetWorld(),
		DistortedHorizontalFOV, DistortedAspectRatio,
		UndistortOverscanFactor, OutputRenderTarget,
		OutputMultiply, OutputAdd);
}
PRAGMA_ENABLE_DEPRECATION_WARNINGS
