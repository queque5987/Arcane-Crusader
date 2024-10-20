#include "CUserWidget_ListedStage.h"
#include "CustomDataTables.h"
#include "IPlayerUIController.h"

void UCUserWidget_ListedStage::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	MapName = ListItemObject->GetName();
	StageName->SetText(FText::FromString(MapName));

	StageButton->OnClicked.AddDynamic(this, &UCUserWidget_ListedStage::OnButtonClicked);
}

void UCUserWidget_ListedStage::SwitchPressed(bool Pressed)
{
	StageBG->SetColorAndOpacity(
		FLinearColor(
			1.f, 1.f, 1.f,
			Pressed ? 1.f : 0.4f
		)
	);
}

void UCUserWidget_ListedStage::OnButtonClicked()
{
	SwitchPressed(!bPressed);
	IIPlayerUIController* UIController = Cast<IIPlayerUIController>(GetOwningPlayer());
	if (UIController != nullptr)
	{
		UIController->SetPressedButton(this);
	}
	//OnStageSelected.ExecuteIfBound(MapName);
}

