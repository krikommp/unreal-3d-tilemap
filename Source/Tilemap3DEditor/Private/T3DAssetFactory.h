// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Factories/Factory.h"
#include "T3DAssetFactory.generated.h"

UCLASS()
class TILEMAP3DEDITOR_API UT3DAssetFactory : public UFactory
{
	GENERATED_UCLASS_BODY()
	
	//~ Begin UFactory interface
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn, FName CallingContext) override;
	//~ Begin UFactory interface
};
