// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DialogueModifiers.h"
#include "CharacterDefinition.generated.h"

USTRUCT(BlueprintType)
struct FCharacterDefinition
{
	GENERATED_BODY()
	
	FCharacterDefinition();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character")
	mutable FName ID;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character")
	bool bIsGeneric = true;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Dialogue", meta=(EditCondition = "!bIsGeneric", EditConditionHides))
	class UDialogueType* Type = nullptr;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Responses", meta=(EditCondition = "!bIsGeneric", EditConditionHides))
	TArray<class UDialogueResponse*> Responses;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Audio", meta=(InlineEditConditionToggle))
	bool bHasAudioClip = false;
	
	UPROPERTY(EditAnywhere, Instanced, BlueprintReadWrite, Category = "Audio", meta=(EditCondition = "bHasAudioClip"))
	class UDialogueAudio* Audio = nullptr;

	bool operator==(const FCharacterDefinition& Other) const
	{
		return (Name.EqualTo(Other.Name) &&
				bIsGeneric == Other.bIsGeneric &&
				Type == Other.Type &&
				Responses == Other.Responses);
	}

	void SetCharacterId(const FName& NewId) const { ID = NewId; }
	
};

USTRUCT(BlueprintType)
struct FLevelDialogue
{
	GENERATED_BODY()

public:
	FLevelDialogue();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Level")
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Characters", meta=(TitleProperty="{Name} [{ID}]"))
	TArray<FCharacterDefinition> Characters;

	bool operator==(const TSoftObjectPtr<UWorld>& SearchLevel) const
	{
		return Level.Get() == SearchLevel.Get();
	}
};