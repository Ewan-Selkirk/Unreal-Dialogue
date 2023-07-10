#pragma once

#include "CoreMinimal.h"
#include "DialogueDefinitionReg.h"
#include "Modules/ModuleManager.h"

class FDialogueSystemEditorModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

#if WITH_EDITOR
    virtual EAssetTypeCategories::Type GetDialogueCategory() const { return DialogueCategory; }
#endif

private:
    TSharedPtr<FDialogueDefinitionReg> DialogueDefinitionReg;
    TSharedPtr<FDialogueGenericDefinitionReg> DialogueGenericDefinitionReg;

protected:
    EAssetTypeCategories::Type DialogueCategory;
    
public:
    TSharedPtr<class FSlateStyleSet> StyleSet;
    
};
