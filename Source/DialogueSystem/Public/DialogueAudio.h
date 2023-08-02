// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Sound/SoundWave.h"
#include "DialogueAudio.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class DIALOGUESYSTEM_API UDialogueAudio : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	TSoftObjectPtr<USoundWave> AudioClip;
};


UCLASS(MinimalAPI, NotBlueprintable)
class UDialogueAudioLoop final : public UDialogueAudio
{
	GENERATED_BODY()
};


UCLASS(MinimalAPI, NotBlueprintable)
class UDialogueAudioOneShot final : public UDialogueAudio
{
	GENERATED_BODY()
	
};
