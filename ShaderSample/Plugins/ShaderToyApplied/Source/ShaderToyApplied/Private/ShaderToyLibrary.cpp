// Fill out your copyright notice in the Description page of Project Settings.


#include "ShaderToyLibrary.h"

#include "Logging/MessageLog.h"
#include "Engine/TextureRenderTarget2D.h"
#include "Engine/World.h"
#include "GlobalShader.h"

#include "PipelineStateCache.h"
#include "ProfilingDebugging/RealtimeGPUProfiler.h"
#include "RHIStaticStates.h"
#include "SceneInterface.h"
#include "CommonRenderResources.h"
#include "PixelShaderUtils.h"

void UShaderToyLibrary::DrawSeaToRenderTarget(const UObject* WorldContextObject, float InTime, UTextureRenderTarget2D* OutputRenderTarget)
{
	check(IsInGameThread());

	UWorld* World = WorldContextObject->GetWorld();

	if (!OutputRenderTarget)
	{
		UE_LOG(LogTemp,Warning,TEXT("Please get render target plz"))
		return;
	}

	const FName TextureRenderTargetName = OutputRenderTarget->GetFName();
	FTextureRenderTargetResource* TextureRenderTargetResource = OutputRenderTarget->GameThread_GetRenderTargetResource();

	ERHIFeatureLevel::Type FeatureLevel = World->Scene->GetFeatureLevel();

	if (FeatureLevel < ERHIFeatureLevel::SM5)
	{
		UE_LOG(LogTemp, Warning, TEXT("Please check FeatureLevel plz"))
		return;
	}

	ENQUEUE_RENDER_COMMAND(CaptureCommand)(
		[TextureRenderTargetResource, InTime, TextureRenderTargetName, FeatureLevel](FRHICommandListImmediate& RHICmdList)
		{
			DrawSeaToRenderTarget_RenderThread(
				RHICmdList,
				InTime,
				TextureRenderTargetName,
				TextureRenderTargetResource,
				FeatureLevel);
		}
		);

}

//TGlobalResource<FSeaShaderVertexBuffer> GSeaVertexBuffer;

void UShaderToyLibrary::DrawSeaToRenderTarget_RenderThread(FRHICommandListImmediate& RHICmdList, const float& InTime, const FName& TextureRenderTargetName, FTextureRenderTargetResource* OutTextureRenderTargetResource, ERHIFeatureLevel::Type FeatureLevel)
{
	check(IsInRenderingThread());

#if WANTS_DRAW_MESH_EVENTS
	FString EventName;
	TextureRenderTargetName.ToString(EventName);
	SCOPED_DRAW_EVENTF(RHICmdList, SceneCapture, TEXT("DrawSeaToRenderTarget %s"), *EventName);
#else
	SCOPED_DRAW_EVENT(RHICmdList, DrawUVDisplacementToRenderTarget_RenderThread);
#endif

	FRHITexture2D* RenderTargetTexture = OutTextureRenderTargetResource->GetRenderTargetTexture();

	RHICmdList.Transition(FRHITransitionInfo(RenderTargetTexture, ERHIAccess::SRVMask, ERHIAccess::RTV));
	FRHIRenderPassInfo RPInfo(RenderTargetTexture, ERenderTargetActions::DontLoad_Store);
	RHICmdList.BeginRenderPass(RPInfo, TEXT("DrawSeaToRenderTarget_RenderThread"));
	{



		FGlobalShaderMap* GlobalShaderMap = GetGlobalShaderMap(FeatureLevel);
		TShaderMapRef<FShaderToyPS> PixelShader(GlobalShaderMap);
		TShaderMapRef<FShaderToyVS> VertexShader(GlobalShaderMap);

		FIntPoint DisplacementMapResolution(OutTextureRenderTargetResource->GetSizeX(), OutTextureRenderTargetResource->GetSizeY());
		RHICmdList.SetViewport(
			0, 0, 0.f,
			DisplacementMapResolution.X, DisplacementMapResolution.Y, 1.f);

		FGraphicsPipelineStateInitializer GraphicsPSOInit;
		RHICmdList.ApplyCachedRenderTargets(GraphicsPSOInit);
		GraphicsPSOInit.DepthStencilState = TStaticDepthStencilState<false, CF_Always>::GetRHI();
		GraphicsPSOInit.BlendState = TStaticBlendState<>::GetRHI();
		GraphicsPSOInit.RasterizerState = TStaticRasterizerState<>::GetRHI();
		GraphicsPSOInit.PrimitiveType = PT_TriangleList;
		GraphicsPSOInit.BoundShaderState.VertexDeclarationRHI = GFilterVertexDeclaration.VertexDeclarationRHI;
		GraphicsPSOInit.BoundShaderState.VertexShaderRHI = VertexShader.GetVertexShader();
		GraphicsPSOInit.BoundShaderState.PixelShaderRHI = PixelShader.GetPixelShader();
		SetGraphicsPipelineState(RHICmdList, GraphicsPSOInit, 0);
		
		// Update viewport.
		RHICmdList.SetViewport(
			0, 0, 0.f,
			OutTextureRenderTargetResource->GetSizeX(), OutTextureRenderTargetResource->GetSizeY(), 1.f);

		// Update shader uniform parameters.

		SetShaderParametersLegacyPS(RHICmdList, PixelShader, InTime);


		FPixelShaderUtils::DrawFullscreenQuad(RHICmdList);

		// Draw grid.
		//RHICmdList.DrawIndexedPrimitive(
		//	GScreenRectangleIndexBuffer.IndexBufferRHI,
		//	/*BaseVertexIndex=*/ 0,
		//	/*MinIndex=*/ 0,
		//	/*NumVertices=*/ 3,
		//	/*StartIndex=*/ 6,
		//	/*NumPrimitives=*/ 1,
		//	/*NumInstances=*/ 1);
	}
	RHICmdList.EndRenderPass();
	RHICmdList.Transition(FRHITransitionInfo(RenderTargetTexture, ERHIAccess::RTV, ERHIAccess::SRVMask));
}
