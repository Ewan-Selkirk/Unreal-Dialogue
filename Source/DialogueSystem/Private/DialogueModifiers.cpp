// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.


#include "DialogueModifiers.h"

//~ Begin UDialogueType Functions //

FText UDialogueTypeRandom::GetLineOfDialogue(bool& bIsSuccessful)
{
	bIsSuccessful = true;
	return GetRandomLine();
}

FText UDialogueTypeContinuous::GetLineOfDialogue(bool& bIsSuccessful)
{
	// There are no dialogue options, therefore return false.
	if (DialogueLines.Num() == 0)
	{
		bIsSuccessful = false;
		return Super::GetLineOfDialogue(bIsSuccessful);
	}

	// The final line of dialogue has been reached, therefore return false.
	if (Index >= DialogueLines.Num() - 1)
	{
		bIsSuccessful = false;
		return Super::GetLineOfDialogue(bIsSuccessful);
	}

	// There are still lines of dialogue, therefore return true and the next line of dialogue.
	if (Index < DialogueLines.Num() - 1)
	{
		bIsSuccessful = true;
		return DialogueLines[++Index];
	}

	return Super::GetLineOfDialogue(bIsSuccessful);
	
}

void UDialogueTypeContinuous::Reset()
{
	Super::Reset();
	Index = -1;
}

FText UDialogueTypeConditional::GetLineOfDialogue(bool& bIsSuccessful)
{
	return Condition->CanDialogueTrigger() ?
		TypeAfterCondition->GetLineOfDialogue(bIsSuccessful) : FailureDialogue->GetLineOfDialogue(bIsSuccessful);
}

bool UDialogueTypeConditional::ShouldDisplayOnce()
{
	return Condition->CanDialogueTrigger() ?
		TypeAfterCondition->ShouldDisplayOnce() : FailureDialogue->ShouldDisplayOnce();
}

void UDialogueTypeConditional::Reset()
{
	Super::Reset();
	if (TypeAfterCondition && TypeAfterCondition->IsValidLowLevel()) { TypeAfterCondition->Reset(); }
	if (FailureDialogue && FailureDialogue->IsValidLowLevel()) { FailureDialogue->Reset(); }
	
}

FText UDialogueTypeMultiConditional::GetLineOfDialogue(bool& bIsSuccessful)
{
	return Super::GetLineOfDialogue(bIsSuccessful);
}

FText UDialoguePay::GetDisplayText() const
{
	return FText::Format(Super::GetDisplayText(), Cost);
}

//~ End UDialogueType Functions //
