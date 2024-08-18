#include "T3DAssetFactory.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(T3DAssetFactory)

UT3DAssetFactory::UT3DAssetFactory(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SupportedClass = UT3DAsset::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UT3DAssetFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags,
	UObject* Context, FFeedbackContext* Warn, FName CallingContext)
{
	UT3DAsset* MyAsset = NewObject<UT3DAsset>(InParent, InName, Flags | RF_Transactional);
	return MyAsset;
}
