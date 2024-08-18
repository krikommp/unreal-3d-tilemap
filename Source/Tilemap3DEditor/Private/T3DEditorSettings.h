#pragma once

#include "Materials/MaterialInterface.h"
#include "T3DEditorSettings.generated.h"

UCLASS(Config="Tilemap3DEditor")
class TILEMAP3DEDITOR_API UT3DEditorSettings : public UObject
{
	GENERATED_BODY()

public:
	UPROPERTY(Config, EditAnywhere, Category="Collision")
	TSoftObjectPtr<UMaterialInterface> CollisionPlaneMat;

	UPROPERTY(Config, EditAnywhere, Category="Collision")
	TSoftObjectPtr<UStaticMesh> CollisionPlaneMesh;
};
