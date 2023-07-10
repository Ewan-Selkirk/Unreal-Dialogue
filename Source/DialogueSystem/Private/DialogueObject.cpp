// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.


#include "DialogueObject.h"

#include "DialogueSubsystem.h"
#include "Misc/DataValidation.h"

#if WITH_EDITOR
EDataValidationResult UDialogueObject::IsDataValid(FDataValidationContext& Context)
{
	bool bIsValid = true;
	
	
	for (auto LevelData : Levels)
	{
		// Will basically always error out. Gonna just disable it for now.
		/*if (!TSoftObjectPtr<UWorld>(LevelData.Level))
		{
			Context.AddError(FText::FromString("A level reference is needed for the dialogue system.\nPlease remove or fill in any blank entries."));
			bIsValid = false;
		}*/

		for (auto Character : LevelData.Characters)
		{
			
			if (Character.ID.IsNone())
			{
				Context.AddError(FText::FromString("Every character requires an ID (represented as 'Character_Name.Level_Name'."));
				bIsValid = false;
			}
			
			if (Character.Name.IsEmpty())
			{
				Context.AddError(FText::FromString("A character needs a valid name.\nPlease make sure all characters have names."));
				bIsValid = false;
			}
		}
	}
	
	return bIsValid ? EDataValidationResult::Valid : EDataValidationResult::Invalid;
}
#endif
#if WITH_EDITORONLY_DATA

void UDialogueObject::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	UE_LOG(LogDialogue, Log, TEXT("[Dialogue System] Dialogue Property Changed: %s"), *PropertyChangedEvent.Property->NamePrivate.ToString());

	if (const FName PropertyName = PropertyChangedEvent.Property->NamePrivate;
		PropertyName == FName("Name") || PropertyName == FName("Level"))
	{
		GenerateCharacterIDs();
	}
}
#endif

void UDialogueObject::GenerateCharacterIDs()
{
	for (const auto& LevelData : Levels)
	{
		auto Level = LevelData.Level;

		for (const auto& Character : LevelData.Characters)
		{
			FString temp = Character.Name.ToString();
			Character.SetCharacterId(FName(temp.Append(TEXT(".")).Append(Level.GetAssetName()).Replace(TEXT(" "), TEXT("_"))));
		}
	}
}

/*#if WITH_EDITORONLY_DATA
void UDialogueObject::PreSave(FObjectPreSaveContext SaveContext)
{

	for (FLevelDialogue LevelData : Levels)
	{
		for (FCharacterDefinition Character : LevelData.Characters)
		{
			Character.SetCharacterId(UDialogueUtilities::GenerateCharacterId(Character, LevelData));
			UE_LOG(LogDialogue, Log, TEXT("[Dialogue System] Attempting to set Character ID for character: %s"), *Character.Name.ToString())
			UE_LOG(LogDialogue, Log, TEXT("[Dialogue System] Generated ID: %s"), *UDialogueUtilities::GenerateCharacterId(Character, LevelData).ToString())
			UE_LOG(LogDialogue, Log, TEXT("[Dialogue System] ID value: %s"), *Character.ID.ToString())
		}
	}
	
	Super::PreSave(SaveContext);
}
#endif*/
