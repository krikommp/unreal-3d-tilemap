// Fill out your copyright notice in the Description page of Project Settings.


#include "T3DMapBuilderRefreshWidget.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION
#define LOCTEXT_NAMESPACE TILEMAP_3D_LOCTEXT_NAMESPACE

void ST3DMapBuilderRefreshWidget::Construct(const FArguments& InArgs)
{
	ChildSlot
	[
		SNew(SButton)
		.OnClicked_Lambda([this]()
		{
			return FReply::Handled();
		})
		[
			SNew(STextBlock)
			.Justification(ETextJustify::Center)
			.Text(LOCTEXT("MapBuilderRefreshButtonNameLabel", "Refresh"))
		]
	];
}

#undef LOCTEXT_NAMESPACE
END_SLATE_FUNCTION_BUILD_OPTIMIZATION
