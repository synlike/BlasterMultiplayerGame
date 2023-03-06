// Fill out your copyright notice in the Description page of Project Settings.


#include "OverheadWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/PlayerState.h"

void UOverheadWidget::SetDisplayText(FString TextToDisplay)
{
	if (DisplayText)
	{
		DisplayText->SetText(FText::FromString(TextToDisplay));
	}
}

FString UOverheadWidget::GetPlayerNetRole(APawn* InPawn)
{
	ENetRole RemoteRole = InPawn->GetRemoteRole();
	FString Role;

	switch (RemoteRole)
	{
		case ENetRole::ROLE_Authority:
			Role = FString("Authority");
			break;

		case ENetRole::ROLE_AutonomousProxy:
			Role = FString("Autonomous Proxy");
			break;

		case ENetRole::ROLE_SimulatedProxy:
			Role = FString("Simulated Proxy");
			break;

		case ENetRole::ROLE_None:
			Role = FString("None");
			break;
	}

	FString RemoteRoleString = FString::Printf(TEXT("Remote Role : %s"), *Role);

	return RemoteRoleString;
	//SetDisplayText(RemoteRoleString);
}

FString UOverheadWidget::GetPlayerName(APawn* InPawn)
{
	FString PlayerName = FString("Unknown");

	APlayerState* PlayerState = InPawn->GetPlayerState();
	if (PlayerState)
	{
		PlayerName = PlayerState->GetPlayerName();
	}

	return PlayerName;
}

void UOverheadWidget::ShowOverheadText(FString PlayerName, FString PlayerNetRole)
{
	FString OverheadText = FString::Printf(TEXT("PlayerName : %s \n PlayerNetRole : %s"), *PlayerName, *PlayerNetRole);
	SetDisplayText(OverheadText);
}

void UOverheadWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
	RemoveFromParent();
	Super::OnLevelRemovedFromWorld(InLevel, InWorld);
}
