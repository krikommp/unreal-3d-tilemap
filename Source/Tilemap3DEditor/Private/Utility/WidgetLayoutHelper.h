#pragma once

namespace T3D
{
	void TitleSlot(TSharedPtr<SVerticalBox> VerticalBox, const FText& InLabel, const EVerticalAlignment VAlign = VAlign_Top);
	SVerticalBox::FScopedWidgetSlotArguments NextVSlot(TSharedPtr<SVerticalBox> VerticalBox, const FText& InLabel = FText::GetEmpty());
	SVerticalBox::FScopedWidgetSlotArguments NextHSlot(TSharedPtr<SHorizontalBox> HorizontalBox, const FText& InLabel = FText::GetEmpty(), EHorizontalAlignment HAlign = HAlign_Fill);
	SHorizontalBox::FScopedWidgetSlotArguments NextVCheckSlot(TSharedPtr<SVerticalBox> VerticalBox, TArray<TSharedPtr<SHorizontalBox>>& ContentBoxArray, const FText& InLabel = FText::GetEmpty());
}