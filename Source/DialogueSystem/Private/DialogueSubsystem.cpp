// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.

#include "DialogueSubsystem.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "Engine/AssetManager.h"
#include "Engine.h"

DEFINE_LOG_CATEGORY(LogDialogue)

UDialogueSubsystem::UDialogueSubsystem()
{
	
}

void UDialogueSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	// Load Dialogue Objects (I think?)
	FAssetRegistryModule& AssetRegistry = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
	UAssetManager& AssetManager = UAssetManager::Get();

	// Create a filter to get the objects
	FARFilter AssetFilter;
	AssetFilter.ClassPaths.Add(UDialogueObject::StaticClass()->GetClassPathName());
	AssetFilter.ClassPaths.Add(UDialogueGenericObject::StaticClass()->GetClassPathName());
	AssetFilter.PackagePaths.Add("/Game/DialogueSystem");
	AssetFilter.bRecursivePaths = true;

	TArray<FAssetData> DialogueAssets;
	AssetRegistry.Get().GetAssets(AssetFilter, DialogueAssets);
	
	for (const FAssetData& AssetData : DialogueAssets)
	{
		// FPrimaryAssetId AssetId(AssetData.GetPrimaryAssetId().PrimaryAssetName, AssetData.PackageName);
		
		PrimaryAssetIds.Add(AssetData.GetPrimaryAssetId());
	}

	const FStreamableDelegate Delegate = FStreamableDelegate::CreateUObject(this, &UDialogueSubsystem::OnAssetsLoaded);
	AssetManager.LoadPrimaryAssets(PrimaryAssetIds, {}, Delegate);
}

void UDialogueSubsystem::Deinitialize()
{
	Super::Deinitialize();
	ResetDialogueSystem();
}

void UDialogueSubsystem::GetCharacterDialogue(TSoftObjectPtr<UWorld> Level, FText Name,
	FCharacterDefinition& Character, bool& bSuccessful)
{
	for (UDialogueObject* Definition : DialogueObjects)
	{
		for (FLevelDialogue& LevelData : Definition->Levels)
		{
			if (LevelData.Level.Get() == Level.Get())
			{
				for (FCharacterDefinition CharacterDefinition : LevelData.Characters)
				{
					if (!CharacterDefinition.Name.EqualTo(Name)) continue;

					Character = CharacterDefinition;
					CurrentCharacter = Character;
					bSuccessful = true;
					return;
				}
			}
		}
	}

	bSuccessful = false;
}

FText UDialogueSubsystem::GetGenericDialogue()
{
	if (GenericLines.Num() == 0)
	{
		return FText::FromString("Could not find any Generic Dialogue Objects. Did you forget to create one?");
	}

	return GenericLines[FMath::RandRange(0, GenericLines.Num() - 1)];
}

void UDialogueSubsystem::GetCharacterDefinitionById(const FName CharacterId, FCharacterDefinition& CharacterDefinition,
                                                    bool& bSuccessful)
{

	for (UDialogueObject* Definition : DialogueObjects)
	{
		for (FLevelDialogue& LevelData : Definition->Levels)
		{
			for (FCharacterDefinition& Character : LevelData.Characters)
			{
				if (Character.ID == CharacterId)
				{
					CharacterDefinition = Character;
					CurrentCharacter = CharacterDefinition;
					bSuccessful = true;
					return;
				}
			}
		}
	}

	bSuccessful = false;
	
}

FName UDialogueSubsystem::CreateCharacterId(FText CharacterName, TSoftObjectPtr<UWorld> Level)
{
	FString WorldName = Level->GetName().Replace(TEXT(" "), TEXT("_"));
	FString Name = CharacterName.ToString().Replace(TEXT(" "), TEXT("_"));

	return FName(Name.Append(".").Append(WorldName));
}

FName UDialogueSubsystem::CreateCharacterIdCurrentLevel(FText CharacterName)
{
	FString WorldName = GEngine->GameViewport->GetWorld()->GetName().Replace(TEXT(" "), TEXT("_"));
	FString Name = CharacterName.ToString().Replace(TEXT(" "), TEXT("_"));

	return FName(Name.Append(".").Append(WorldName));
}

void UDialogueSubsystem::ResetDialogueSystem()
{
	for (const auto DialogueObj : DialogueObjects)
	{
		if (!IsValid(DialogueObj)) continue;
		
		for(auto LevelDef : DialogueObj->Levels)
		{
			for (const auto& Character: LevelDef.Characters)
			{
				if (!IsValid(Character.Type)) continue;
				CastChecked<UDialogueType>(Character.Type)->Reset();
			}
		}
	}

	State = EDialogueState::Dialogue;
	bCanSkip = true;
	bCanSummon = true;
}

/*TArray<FCharacterDefinition> UDialogueSubsystem::GetAllCharactersFromCurrentLevel()
{
	TSoftObjectPtr<UWorld> World = GEngine->GetWorldContextFromGameViewport(GEngine->GameViewport)->World();

	return DialogueObjects[0]->Levels.FindByKey(World)->Characters;
}*/

void UDialogueSubsystem::OnAssetsLoaded()
{

	UAssetManager &Manager = UAssetManager::Get();
	for (FPrimaryAssetId Id : PrimaryAssetIds)
	{
		auto Path = Manager.GetPrimaryAssetPath(Id);

		FSoftObjectPtr Ptr(Path);
		UObject *Obj = Ptr.LoadSynchronous();
		if (!Obj)
			UE_LOG(LogTemp, Error, TEXT("Failed to load primary object %s using path %s"), *Id.ToString(), *Path.ToString());	
	}

	
	// Standard Dialogue Definitions
	for (TObjectIterator<UDialogueObject> DialogueObject; DialogueObject; ++DialogueObject)
	{
		
		if (DialogueObjects.Contains(*DialogueObject)) continue;
		
		UE_LOG(LogDialogue, Log, TEXT("[Dialogue System] Registered dialogue definition: %s"), *DialogueObject->GetName())
		DialogueObjects.Add(*DialogueObject);
	}
	
	/*for (auto Dialogue : GetMutableDefault<UDialogueSystemSettings>()->DialogueDefinitions)
	{
		// UE_LOG(LogDialogue, Log, TEXT("[Dialogue System] Registered dialogue definition: %s"), *Dialogue.Get()->GetName())
		DialogueObjects.AddUnique(Dialogue.Get());
		
	}*/

	// Generic Dialogue Definitions
	/*for (auto GenericDialogue : GetMutableDefault<UDialogueSystemSettings>()->GenericDialogueDefinitions)
	{
		// UE_LOG(LogDialogue, Log, TEXT("[Dialogue System] Registered generic dialogue definition: %s"), *GenericDialogue.Get()->GetName())
		for (auto [Line, _] : GenericDialogue.Get()->GetGenericDialogue())
		{
			GenericLines.Add(Line);	
		}
	}*/
	
	for (TObjectIterator<UDialogueGenericObject> GenericObject; GenericObject; ++GenericObject)
	{
		for (auto [Line, _] : GenericObject->GetGenericDialogue())
		{
			GenericLines.Add(Line);
		}
	}
}

//~ Begin UDialogueUtilities
FName UDialogueUtilities::GenerateCharacterId(const FLevelDialogue& Level, const FCharacterDefinition& Character)
{
	FString Temp = Level.Level.Get()->GetName();	
	
	return FName(Temp.Append(".").Append(Character.Name.ToString()));
}
//~ End UDialogueUtilities
