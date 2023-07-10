// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "DialogueDefinitionFactory.generated.h"

/**
 * 
 */
UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueDefinitionFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDialogueDefinitionFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};

UCLASS()
class DIALOGUESYSTEMEDITOR_API UDialogueGenericDefinitionFactory : public UFactory
{
	GENERATED_BODY()

public:
	UDialogueGenericDefinitionFactory();
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};