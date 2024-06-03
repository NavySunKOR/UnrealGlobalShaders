// Copyright Epic Games, Inc. All Rights Reserved.

#include "ShaderToyApplied.h"
#include "Interfaces/IPluginManager.h"
#define LOCTEXT_NAMESPACE "FShaderToyAppliedModule"

void FShaderToyAppliedModule::StartupModule()
{
	FString PluginShaderDir = FPaths::Combine(IPluginManager::Get().FindPlugin(TEXT("ShaderToyApplied"))->GetBaseDir(), TEXT("Shaders"));
	AddShaderSourceDirectoryMapping(TEXT("/ShaderToyApplied"), PluginShaderDir);
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FShaderToyAppliedModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FShaderToyAppliedModule, ShaderToyApplied)