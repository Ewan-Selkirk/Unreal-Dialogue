// Copyright Epic Games, Inc. All Rights Reserved.

#include "DialogueSystem.h"

// #include "DialogueSystemSettings.h"
#if WITH_EDITOR
#include "ISettingsModule.h"
#endif

#define LOCTEXT_NAMESPACE "FDialogueSystemModule"

void FDialogueSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	/*FTextFormatter::Get().RegisterTextArgumentModifier(FTextFormatString::MakeReference(TEXT("cost")),
		[](const FTextFormatString& String, const FTextFormatPatternDefinitionConstRef& Pattern)
		{
			return FTextFormatArgumentMod
		});*/

/*#if WITH_EDITOR
	// Register Project Settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings("Project", "Plugins", "Dialogue System",
		LOCTEXT("DialogueSystemSettingsName", "Dialogue System"),
		LOCTEXT("DialogueSystemSettingsDesc", "Register dialogue objects here."),
		GetMutableDefault<UDialogueSystemSettings>()
		);
	}
#endif*/
	
}

void FDialogueSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

#if WITH_EDITOR
	//Unregister Project Settings
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "DialogueSystem");
	}
#endif
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDialogueSystemModule, DialogueSystem)