#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
    Super::BeginPlay();

    auto ControlledTank = GetControlledTank();

    if (ControlledTank) {
        UE_LOG(LogTemp, Warning, TEXT("GetControlledTank: %s"), *(ControlledTank->GetName()));
    } else {
        UE_LOG(LogTemp, Error, TEXT("Not controlling a tank"));
    }
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}
