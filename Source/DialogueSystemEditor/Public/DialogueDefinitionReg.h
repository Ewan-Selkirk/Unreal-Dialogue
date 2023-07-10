// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AssetTypeActions_Base.h"
#include "Styling/SlateStyle.h"
#include "Styling/SlateStyleMacros.h"
#include "UObject/Object.h"

/**
 * 
 */
class FDialogueDefinitionReg final : public FAssetTypeActions_Base
{
	
public:
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;

	virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;
	virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;
};

class FDialogueGenericDefinitionReg final : public FAssetTypeActions_Base
{
public:
	virtual FText GetName() const override;
	virtual UClass* GetSupportedClass() const override;
	virtual FColor GetTypeColor() const override;
	virtual uint32 GetCategories() override;
	virtual FText GetAssetDescription(const FAssetData& AssetData) const override;

	virtual const FSlateBrush* GetIconBrush(const FAssetData& InAssetData, const FName InClassName) const override;
	virtual const FSlateBrush* GetThumbnailBrush(const FAssetData& InAssetData, const FName InClassName) const override;
};


class FDialogueSlateStyle final : public FSlateStyleSet
{
public:
	FDialogueSlateStyle() : FSlateStyleSet("DialogueSystemStyle")
	{
		// SetParentStyleName(FAppStyle::GetAppStyleSetName());

		/*FSlateStyleSet::SetContentRoot(FPaths::EnginePluginsDir() / TEXT("DialogueSystem/Content/Editor/Slate"));

		static const FVector2D Icon16 = FVector2D(16.0f, 16.0f);
		static const FVector2D Icon64 = FVector2D(64.0f, 64.0f);

		// Set("DialogueDefinition_Small", new IMAGE_BRUSH_SVG("Icons/DialogueDefinition_16", Icon16));
		Set("DialogueSystem_Large", new IMAGE_BRUSH_SVG("Icons/DialogueDefinition_64", Icon64));

		Set("ClassIcon.DialogueDefinition", new IMAGE_BRUSH_SVG("Icons/DialogueDefinition_16", Icon16));
		Set("ClassThumbnail.DialogueDefinition", new IMAGE_BRUSH_SVG("Icons/DialogueDefinition_64", Icon64));*/
	}
}; 
