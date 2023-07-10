// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "CharacterDefinition.h"
#include "DialogueObject.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "DialogueSubsystem.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogDialogue, Log, All);

UENUM(BlueprintType)
enum EDialogueState
{
	Dialogue,
	Response,
	ResponseDialogue		UMETA(DisplayName="Dialogue Following Response")
};

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEM_API UDialogueSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
	UDialogueSubsystem();
	
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void GetCharacterDialogue(TSoftObjectPtr<UWorld> Level, FText Name, FCharacterDefinition& Character, bool& bSuccessful);

	UFUNCTION(BlueprintCallable, Category="Dialogue|Generic")
	FText GetGenericDialogue();

	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void GetCharacterDefinitionById(FName CharacterId, FCharacterDefinition& CharacterDefinition, bool& bSuccessful);

	UFUNCTION(BlueprintCallable, Category="Dialogue|Utilities")
	FName CreateCharacterId(FText CharacterName, TSoftObjectPtr<UWorld> Level);

	UFUNCTION(BlueprintCallable, Category="Dialogue|Utilities")
	FName CreateCharacterIdCurrentLevel(FText CharacterName);
	
	/*UFUNCTION(BlueprintCallable, Category="Dialogue|")
	TArray<FCharacterDefinition> GetAllCharactersFromCurrentLevel();*/

	UFUNCTION(BlueprintCallable, Category="Dialogue")
	void ResetDialogueSystem();

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Dialogue|Utilities")
	FCharacterDefinition GetCurrentCharacter() { return CurrentCharacter; }

	UPROPERTY(BlueprintReadWrite, Category="Dialogue|Subsystem|Variables")
	bool bCanSummon = true;

	UPROPERTY(BlueprintReadWrite, Category="Dialogue|Subsystem|Variables")
	bool bCanSkip = true;

	UPROPERTY(BlueprintReadWrite, Category="Dialogue|Subsystem|Variables")
	TEnumAsByte<EDialogueState> State = EDialogueState::Dialogue;

private:
	UPROPERTY()
	TArray<FText> GenericLines;

	UPROPERTY(BlueprintGetter=GetCurrentCharacter, Category="Dialogue")
	FCharacterDefinition CurrentCharacter;

	UPROPERTY()
	TArray<FPrimaryAssetId> PrimaryAssetIds;

	void OnAssetsLoaded();

protected:
	UPROPERTY()
	TArray<UDialogueObject*> DialogueObjects;
};

UCLASS()
class UDialogueUtilities : public UObject
{

	GENERATED_BODY()
	
public:
	static FName GenerateCharacterId(const FLevelDialogue& Level, const FCharacterDefinition& Character);
	
};
