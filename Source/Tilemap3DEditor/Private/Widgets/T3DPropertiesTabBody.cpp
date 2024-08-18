#include "T3DPropertiesTabBody.h"

#include "T3DEditorToolkit.h"
#include "T3DMapBuilderWidget.h"
#include "MapBuilder/T3DMapBuilderRefreshWidget.h"
#include "MapBuilder/T3DMapBuilderStatusWidget.h"
#include "MapBuilder/T3DMapBuilderWidgetContext.h"
#include "Utility/WidgetLayoutHelper.h"

FT3DMapBuilderWidgetContext GBuilderWidgetContext;

void ST3DPropertiesTabBody::Construct(const FArguments& InArgs, TWeakObjectPtr<UT3DAsset> InAsset,
                                      TSharedPtr<FT3DEditorToolkit> InT3DEditor)
{
	T3DAsset = InAsset;

	SSingleObjectDetailsPanel::Construct(
		SSingleObjectDetailsPanel::FArguments().HostCommandList(InT3DEditor->GetToolkitCommands()).
		                                        HostTabManager(InT3DEditor->GetTabManager()),
		/*bAutomaticallyObserveViaGetObjectToObserve=*/ true, /*bAllowSearch=*/ true);
}

UObject* ST3DPropertiesTabBody::GetObjectToObserve() const
{
	return T3DAsset.Get();
}

TSharedRef<SWidget> ST3DPropertiesTabBody::PopulateSlot(TSharedRef<SWidget> PropertyEditorWidget)
{
	PropertyEditorWidget->SetEnabled(TAttribute<bool>::Create([this]()-> bool
	{
		return !GBuilderWidgetContext.bMapBuilderEditing.Get();
	}));

	TSharedPtr<SVerticalBox> WidgetVerticalBox = SNew(SVerticalBox);

	T3D::NextVSlot(WidgetVerticalBox)
	[
		PropertyEditorWidget
	];

	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(ST3DMapBuilderRefreshWidget)
	];

	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(ST3DMapBuilderStatusWidget)
	];

	T3D::NextVSlot(WidgetVerticalBox)
	[
		SNew(SBorder)
		.BorderImage(new FSlateRoundedBoxBrush(FAppStyle::Get().GetSlateColor("Colors.Header"), 6.0f))
		.Visibility_Lambda([this](){ return !GBuilderWidgetContext.bMapBuilderEditing.Get() ? EVisibility::Collapsed : EVisibility::Visible; })
		[
			SNew(ST3DMapBuilderWidget, T3DAsset)
		]
	];
	
	return SNew(SBorder)
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		[
			WidgetVerticalBox.ToSharedRef()
		]
	];
}
