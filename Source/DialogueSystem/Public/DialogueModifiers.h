// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/Object.h"
#include "Engine.h"
#include "DialogueModifiers.generated.h"

//~ Begin UDialogueType Declaration //
/**
 * Types of Dialogue
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class DIALOGUESYSTEM_API UDialogueType : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Dialogue|Type")
	virtual bool ShouldDisplayOnce() { return true; }

	UFUNCTION(BlueprintCallable, Category="Dialogue|Type")
	virtual FText GetLineOfDialogue(bool& bIsSuccessful) { return FText::FromString("Poop"); }

	virtual void Reset() {}

};

UCLASS(Abstract, NotBlueprintable, EditInlineNew, CollapseCategories)
class DIALOGUESYSTEM_API UDialogueType_MultiReturn : public UDialogueType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="")
	TArray<FText> DialogueLines;

	virtual bool ShouldDisplayOnce() override { return false; }
};

UCLASS(Abstract, NotBlueprintable, EditInlineNew, CollapseCategories)
class DIALOGUESYSTEM_API UDialogueType_ConditionalReturn : public UDialogueType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Instanced, Category="Dialogue", meta=(AllowedClasses="/Script/DialogueSystem.DialogueTypeRandom,/Script/DialogueSystem.DialogueTypeContinuous", ExactClass=true))
	class UDialogueType* FailureDialogue;
};

UCLASS(NotBlueprintable, MinimalAPI)
class UDialogueTypeSingleLine final : public UDialogueType
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Dialogue")
	FText LineOfDialogue;

	virtual FText GetLineOfDialogue(bool& bIsSuccessful) override { bIsSuccessful = true; return LineOfDialogue; }
};

UCLASS(NotBlueprintable, MinimalAPI)
class UDialogueTypeRandom final : public UDialogueType_MultiReturn
{
	GENERATED_BODY()

public:
	virtual FText GetLineOfDialogue(bool& bIsSuccessful) override;
	virtual bool ShouldDisplayOnce() override { return true; }

private:
	UFUNCTION(BlueprintCallable, Category = "Dialogue|Type|Random")
	FText GetRandomLine() { return DialogueLines[FMath::RandRange(0, DialogueLines.Num() - 1)]; }
};


UCLASS(NotBlueprintable, MinimalAPI)
class UDialogueTypeContinuous final : public UDialogueType_MultiReturn
{
	GENERATED_BODY()

public:
	virtual FText GetLineOfDialogue(bool& bIsSuccessful) override;
	virtual void Reset() override;

protected:
	UPROPERTY()
	int8 Index = -1;
};


UCLASS(NotBlueprintable, MinimalAPI)
class UDialogueTypeConditional final : public UDialogueType_ConditionalReturn
{
	GENERATED_BODY()

public:
	virtual FText GetLineOfDialogue(bool& bIsSuccessful) override;
	virtual bool ShouldDisplayOnce() override;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category="Dialogue")
	class UDialogueTrigger* Condition;

	UPROPERTY(EditAnywhere, Instanced, BlueprintReadOnly, Category="Dialogue", meta=(EditCondition="Condition != nullptr", EditConditionHides, AllowedClasses="/Script/DialogueSystem.DialogueTypeRandom,/Script/DialogueSystem.DialogueTypeContinuous", ExactClass=true))
	class UDialogueType* TypeAfterCondition;
};


UCLASS(NotBlueprintable, MinimalAPI)
class UDialogueTypeMultiConditional final : public UDialogueType_ConditionalReturn
{
	GENERATED_BODY()

public:
	virtual FText GetLineOfDialogue(bool& bIsSuccessful) override;

	UPROPERTY(EditAnywhere, Instanced, Category="Dialogue")
	TMap<class UDialogueTrigger*, class UDialogueType*> Conditions;

};

//~ End UDialogueType Declaration //

//~ Begin UDialogueTrigger Declaration //
/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories, meta=(ShowWorldContextPin))
class DIALOGUESYSTEM_API UDialogueTrigger : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = "Trigger")
	bool CanDialogueTrigger();
	virtual bool CanDialogueTrigger_Implementation() { return false; }

	UFUNCTION(BlueprintCallable, Category="Dialogue")
	static UWorld* GetWorldContext() { return GEngine->GetCurrentPlayWorld(); }

};
//~ End UDialogueTrigger Declaration //

//~ Begin UDialogueResponse Declaration //
/**
 * Dialogue Responses - Options that the player can choose after an NPC has said their dialogue.
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, CollapseCategories)
class DIALOGUESYSTEM_API UDialogueResponse : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintGetter="GetDisplayText", BlueprintReadWrite, Category="Dialogue")
	FText DisplayText;

	UFUNCTION(BlueprintGetter, Category="Dialogue|Type")
	virtual FText GetDisplayText() const { return DisplayText; }

	UFUNCTION(BlueprintCallable, BlueprintPure, Category="Dialogue|Type")
	virtual bool CanAddToList() { return true; }

};

UCLASS(NotBlueprintable, MinimalAPI, meta=(DisplayName = "Interact With Character"))
class UDialogueInteract final : public UDialogueResponse
{
	GENERATED_BODY()

public:
	/*UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Random")
	TArray<FText> PossibleLines;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="", meta=(DisplayAfter="DisplayText"))
	FText ResponseText;
};

UCLASS(NotBlueprintable, MinimalAPI, meta=(DisplayName = "Pay Character"))
class UDialoguePay final : public UDialogueResponse
{
	GENERATED_BODY()

public:
	virtual FText GetDisplayText() const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pay", meta=(DisplayAfter="DisplayText"))
	uint8 Cost = 0;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pay|Responses", meta=(DisplayAfter="DisplayText"))
	FText PurchaseSuccessResponse;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Pay|Responses", meta=(DisplayAfter="DisplayText"))
	FText PurchaseFailedResponse;
};

UCLASS(NotBlueprintable, MinimalAPI, meta=(DisplayName = "Conditional Response"))
class UDialogueCondition final : public UDialogueResponse
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Instanced, Category="Dialogue")
	class UDialogueTrigger* Condition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Instanced, Category="Dialogue", meta=(EditCondition="Condition != nullptr", EditConditionHides))
	class UDialogueResponse* Response;

	virtual bool CanAddToList() override { return Condition->CanDialogueTrigger(); }
};
//~ End UDialogueResponse Declaration //
