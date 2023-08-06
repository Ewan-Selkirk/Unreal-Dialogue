// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDefinition.h"
#include "Engine/DataAsset.h"
#include "DialogueObject.generated.h"

UINTERFACE(MinimalAPI, Blueprintable, Category = "Dialogue|Pay")
class UOnPurchaseSuccessful : public UInterface
{
	GENERATED_BODY()
};

class IOnPurchaseSuccessful
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Dialogue|Pay")
	void OnPurchaseSuccessful(uint8 EventIndex, uint8 Cost);
};

/**
 * 
 */
UCLASS(BlueprintType)
class DIALOGUESYSTEM_API UDialogueObject : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
#if WITH_EDITOR
	virtual EDataValidationResult IsDataValid(FDataValidationContext& Context) override;
#endif


#if WITH_EDITORONLY_DATA
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent ) override;
#endif

	FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("DialogueObject", GetFName()); }
	

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category="Dialogue", AssetRegistrySearchable, meta=(TitleProperty = "{Level}"))
	TArray<FLevelDialogue> Levels;

public:
	void GenerateCharacterIDs();

	friend class FDialogueDetails;
	friend class UDialogueSubsystem;

public:
	bool ContainsLevel(const TSoftObjectPtr<UWorld>& Level) const { return Levels.Contains(Level); }
	
	const TArray<FLevelDialogue>& GetAllLevelDialogue() const { return Levels; }
	
};

USTRUCT(BlueprintType)
struct FGenericDialogueLine
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	FText Line;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Dialogue")
	float Weight = 1.0f;
	
};

UCLASS(BlueprintType)
class DIALOGUESYSTEM_API UDialogueGenericObject : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UFUNCTION()
	TArray<FGenericDialogueLine>& GetGenericDialogue() { return LinesOfDialogue; }

	FPrimaryAssetId GetPrimaryAssetId() const override { return FPrimaryAssetId("DialogueGenericObject", GetFName()); }

protected:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Dialogue", AssetRegistrySearchable, meta=(MultiLine))
	TArray<FGenericDialogueLine> LinesOfDialogue;
	
};