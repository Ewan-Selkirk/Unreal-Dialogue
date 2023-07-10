#include "DialogueSystemEditor.h"

#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleRegistry.h"

#define LOCTEXT_NAMESPACE "FDialogueSystemEditorModule"

void FDialogueSystemEditorModule::StartupModule()
{
    DialogueDefinitionReg = MakeShared<FDialogueDefinitionReg>();
    DialogueGenericDefinitionReg = MakeShared<FDialogueGenericDefinitionReg>();
    
    DialogueCategory = FAssetToolsModule::GetModule().Get().RegisterAdvancedAssetCategory(FName(TEXT("Dialogue")),
        LOCTEXT("DialogueAssetCategory", "Dialogue"));
    FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(DialogueDefinitionReg.ToSharedRef());
    FAssetToolsModule::GetModule().Get().RegisterAssetTypeActions(DialogueGenericDefinitionReg.ToSharedRef());

    // Register Slate Style
    StyleSet = MakeShared<FDialogueSlateStyle>();
    StyleSet->SetContentRoot(IPluginManager::Get().FindPlugin("DialogueSystem")->GetBaseDir() / TEXT("Content/Editor/Slate"));

    StyleSet->Set("ClassIcon.DialogueDefinition",
        new FSlateVectorImageBrush(StyleSet->RootToContentDir("Icons/DialogueDefinition_16", TEXT(".svg")), FVector2D(16.0f)));
    StyleSet->Set("ClassThumbnail.DialogueDefinition",
        new FSlateVectorImageBrush(StyleSet->RootToContentDir("Icons/DialogueDefinition_64", TEXT(".svg")), FVector2D(64.0f)));
    
    FSlateStyleRegistry::RegisterSlateStyle(*StyleSet.Get());
}

void FDialogueSystemEditorModule::ShutdownModule()
{
    if (!FModuleManager::Get().IsModuleLoaded("AssetTools")) return;

    FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(DialogueDefinitionReg.ToSharedRef());
    FAssetToolsModule::GetModule().Get().UnregisterAssetTypeActions(DialogueGenericDefinitionReg.ToSharedRef());

    if (StyleSet.IsValid())
    {
        FSlateStyleRegistry::UnRegisterSlateStyle(StyleSet->GetStyleSetName());
    }
    
}

#undef LOCTEXT_NAMESPACE
    
IMPLEMENT_MODULE(FDialogueSystemEditorModule, DialogueSystemEditor)