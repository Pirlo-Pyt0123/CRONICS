// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CRONICSGameMode.generated.h"

class AA_Exoplanetas;

UCLASS(MinimalAPI)
class ACRONICSGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ACRONICSGameMode();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


};



