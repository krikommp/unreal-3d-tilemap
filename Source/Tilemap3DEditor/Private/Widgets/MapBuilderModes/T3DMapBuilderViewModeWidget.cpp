#include "T3DMapBuilderViewModeWidget.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void ST3DMapBuilderViewModeWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(STextBlock)
		.Text(LOCTEXT("ViewModeWidgetNameLabel", "View Mode"))
	];
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
