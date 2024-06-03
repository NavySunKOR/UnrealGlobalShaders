// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "ShaderToyShaders.h"
#include "RenderResource.h"
#include "ShaderToyLibrary.generated.h"

/**
 * 
 */
UCLASS()
class SHADERTOYAPPLIED_API UShaderToyLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Draws UV displacement map within the output render target.
	 * - Red & green channels hold the distortion displacement;
	 * - Blue & alpha channels hold the undistortion displacement.
	 * @param DistortedHorizontalFOV The desired horizontal FOV in the distorted render.
	 * @param DistortedAspectRatio The desired aspect ratio of the distorted render.
	 * @param UndistortOverscanFactor The factor of the overscan for the undistorted render.
	 * @param OutputRenderTarget The render target to draw to. Don't necessarily need to have same resolution or aspect ratio as distorted render.
	 * @param OutputMultiply The multiplication factor applied on the displacement.
	 * @param OutputAdd Value added to the multiplied displacement before storing into the output render target.
	 */
	UFUNCTION(BlueprintCallable, Category = "Lens Distortion")
	static void DrawSeaToRenderTarget(
		const UObject* WorldContextObject,float InTime,
		class UTextureRenderTarget2D* OutputRenderTarget
	);

private:
	static void DrawSeaToRenderTarget_RenderThread(
		FRHICommandListImmediate& RHICmdList,
		const float& InTime,
		const FName& TextureRenderTargetName,
		FTextureRenderTargetResource* OutTextureRenderTargetResource,
		ERHIFeatureLevel::Type FeatureLevel);
	
};
