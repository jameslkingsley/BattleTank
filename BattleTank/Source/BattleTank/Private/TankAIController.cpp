#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
    Super::BeginPlay();

    auto PlayerPawn = GetPlayerTank();
    if (PlayerPawn) {
        UE_LOG(LogTemp, Warning, TEXT("AI Controller: Player: %s"), *(PlayerPawn->GetName()));
    } else {
        UE_LOG(LogTemp, Error, TEXT("AI Controller: Can't find player"));
    }
}

ATank* ATankAIController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const {
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
    if (!PlayerPawn) { return nullptr; }
    return Cast<ATank>(PlayerPawn);
}
