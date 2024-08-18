#include "T3DMapBuilderStatusWidget.h"

#include "T3DMapBuilderWidgetContext.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void ST3DMapBuilderStatusWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SButton)
		.OnClicked_Lambda([this]()
		{
			GBuilderWidgetContext.bMapBuilderEditing = !GBuilderWidgetContext.bMapBuilderEditing.Get();
			return FReply::Handled();
		})
		[
			SAssignNew(StatusText, STextBlock)
			.Justification(ETextJustify::Center)
			.Text_Lambda([this]()
			{
				return !GBuilderWidgetContext.bMapBuilderEditing.Get() ? LOCTEXT("MapBuilderEditState", "Start Editing") : LOCTEXT("MapBuilderEditState", "Stop Editing");
			})
		]
	];
}
#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
