// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GlobalShader.h"

#include "DataDrivenShaderPlatformInfo.h"
#include "ShaderParameterUtils.h"
#include "Logging/MessageLog.h"
#include "ProfilingDebugging/RealtimeGPUProfiler.h"
#include "RHIStaticStates.h"
#include "PipelineStateCache.h"
#include "RHICommandList.h"
/**
 * 
 */

class FShaderToyVS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FShaderToyVS, Global, )
public:
	

	FShaderToyVS() {}
	FShaderToyVS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{

	}

	static bool ShouldCache(EShaderPlatform Platform)
	{
		return true;
	}

};

class FShaderToyPS : public FGlobalShader
{
	DECLARE_EXPORTED_SHADER_TYPE(FShaderToyPS, Global,)
public:
	static bool ShouldCompilePermutation(const FGlobalShaderPermutationParameters& Parameters)
	{
		return IsFeatureLevelSupported(Parameters.Platform, ERHIFeatureLevel::SM5);
	}

	FShaderToyPS(){}
	FShaderToyPS(const ShaderMetaType::CompiledShaderInitializerType& Initializer)
		: FGlobalShader(Initializer)
	{
		iTime.Bind(Initializer.ParameterMap, TEXT("iTime"));
	}

	void SetParameters(
		FRHIBatchedShaderParameters& BatchedParameters, 
		const float& InTime)
	{
		SetShaderValue(BatchedParameters, iTime, InTime);
	}

private:
	LAYOUT_FIELD(FShaderParameter, iTime);

};

IMPLEMENT_SHADER_TYPE(, FShaderToyVS, TEXT("/ShaderToyApplied/ShaderToySea.usf"), TEXT("MainVS"), SF_Vertex);
IMPLEMENT_SHADER_TYPE(, FShaderToyPS, TEXT("/ShaderToyApplied/ShaderToySea.usf"), TEXT("MainPS"), SF_Pixel);


class SHADERTOYAPPLIED_API ShaderToyShaders
{
public:
	ShaderToyShaders();
	~ShaderToyShaders();
};

struct FSeaShaderVertex
{
	FVector4f Position;
	FVector2f UV;
};
//class FSeaShaderVertexDeclaration : public FRenderResource
//{
//public:
//	FVertexDeclarationRHIRef VertexDeclarationRHI;
//
//	virtual void InitRHI(FRHICommandListBase& RHICmdList) override
//	{
//		FVertexDeclarationElementList Elements;
//		uint32 Stride = sizeof(FSeaShaderVertex);
//		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FSeaShaderVertex, Position), VET_Float4, 0, Stride));
//		Elements.Add(FVertexElement(0, STRUCT_OFFSET(FSeaShaderVertex, UV), VET_Float2, 1, Stride));
//		VertexDeclarationRHI = RHICreateVertexDeclaration(Elements);
//	}
//
//	virtual void ReleaseRHI() override
//	{
//		VertexDeclarationRHI->Release();
//	}
//};
//
//class FSeaShaderVertexBuffer : public FVertexBuffer
//{
//public: 
//	/*
//	
//	*/
//	virtual void InitRHI(FRHICommandListBase& RHICmdList) override
//	{
//		TResourceArray<FSeaShaderVertex, VERTEXBUFFER_ALIGNMENT> Vertices;
//		Vertices.SetNumUninitialized(6);
//
//		Vertices[0].Position = FVector4f(-1, 1, 0, 1);
//		Vertices[0].UV = FVector2f(0, 0);
//
//		Vertices[1].Position = FVector4f(1, 1, 0, 1);
//		Vertices[1].UV = FVector2f(1, 0);
//
//		Vertices[2].Position = FVector4f(-1, -1, 0, 1);
//		Vertices[2].UV = FVector2f(0, 1);
//
//		Vertices[3].Position = FVector4f(1, -1, 0, 1);
//		Vertices[3].UV = FVector2f(1, 1);
//
//		FRHIResourceCreateInfo CreateInfo(L"FSeaShaderVertexBuffer", &Vertices);
//
//		VertexBufferRHI = RHICreateVertexBuffer(Vertices.GetResourceDataSize(), BUF_Static, CreateInfo);
//	}
//};