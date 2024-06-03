// Copyright Epic Games, Inc. All Rights Reserved.

#include "FooShader.h"
#include "Interfaces/IPluginManager.h"

#define LOCTEXT_NAMESPACE "FFooShaderModule"

void FFooShaderModule::StartupModule()
{
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("FooShader"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/FooShaderDir"), PluginShaderDir);
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FFooShaderModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FFooShaderModule, FooShader)