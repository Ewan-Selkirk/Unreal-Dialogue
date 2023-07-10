// Copyright Ewan Selkirk <ewan@stick-stack.dev>. All Rights Reserved.


#include "DialogueDefinitionFactory.h"

#include "DialogueObject.h"

UDialogueDefinitionFactory::UDialogueDefinitionFactory()
{
	SupportedClass = UDialogueObject::StaticClass();
	bCreateNew = true;
	
}

UDialogueGenericDefinitionFactory::UDialogueGenericDefinitionFactory()
{
	SupportedClass = UDialogueGenericObject::StaticClass();
	bCreateNew = true;
}


UObject* UDialogueDefinitionFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
                                                      EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDialogueObject>(InParent, InClass, InName, Flags, Context);
}

UObject* UDialogueGenericDefinitionFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName,
	EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UDialogueGenericObject>(InParent, InClass, InName, Flags, Context);
}
