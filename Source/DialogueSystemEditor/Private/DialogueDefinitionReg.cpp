// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.


#include "DialogueDefinitionReg.h"

#include "DialogueObject.h"
#include "DialogueSystemEditor.h"

FText FDialogueDefinitionReg::GetName() const
{
	return FText::FromString(TEXT("Dialogue Definition"));
}

UClass* FDialogueDefinitionReg::GetSupportedClass() const
{
	return UDialogueObject::StaticClass();
}

FColor FDialogueDefinitionReg::GetTypeColor() const
{
	return FColor::FromHex(TEXT("#989aff"));
}

uint32 FDialogueDefinitionReg::GetCategories()
{
	return FModuleManager::GetModuleChecked<FDialogueSystemEditorModule>("DialogueSystemEditor").GetDialogueCategory();
}

FText FDialogueDefinitionReg::GetAssetDescription(const FAssetData& AssetData) const
{
	return NSLOCTEXT("DialogueSystem", "DialogueSystem_DialogueDefinitionDescription",
		"A list of characters and their respective dialogue mapped to separate levels.\n"
		"A definition gets automatically registered by the dialogue subsystem.");
}

const FSlateBrush* FDialogueDefinitionReg::GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const
{
	return FModuleManager::GetModulePtr<FDialogueSystemEditorModule>("DialogueSystemEditor")->StyleSet
		->GetBrush("ClassIcon.DialogueDefinition");
}

const FSlateBrush* FDialogueDefinitionReg::GetThumbnailBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return FModuleManager::GetModulePtr<FDialogueSystemEditorModule>("DialogueSystemEditor")->StyleSet
		->GetBrush("ClassThumbnail.DialogueDefinition");
}

FText FDialogueGenericDefinitionReg::GetName() const
{
	return FText::FromString("Generic Dialogue Definition");
}

UClass* FDialogueGenericDefinitionReg::GetSupportedClass() const
{
	return UDialogueGenericObject::StaticClass();
}

FColor FDialogueGenericDefinitionReg::GetTypeColor() const
{
	return FColor::Emerald;
}

uint32 FDialogueGenericDefinitionReg::GetCategories()
{
	return FModuleManager::GetModuleChecked<FDialogueSystemEditorModule>("DialogueSystemEditor").GetDialogueCategory();	
}

FText FDialogueGenericDefinitionReg::GetAssetDescription(const FAssetData& AssetData) const
{
	return FText::FromString("A dialogue definition used by characters that are marked as generic (they have 'bIsGeneric' set to true.)\n"
						  "A random line will be picked from the list.");
}

const FSlateBrush* FDialogueGenericDefinitionReg::GetIconBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return FAssetTypeActions_Base::GetIconBrush(InAssetData, InClassName);
}

const FSlateBrush* FDialogueGenericDefinitionReg::GetThumbnailBrush(const FAssetData& InAssetData,
	const FName InClassName) const
{
	return FAssetTypeActions_Base::GetThumbnailBrush(InAssetData, InClassName);
}

