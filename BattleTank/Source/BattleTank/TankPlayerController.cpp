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

void ATankPlayerController::Tick(float DeltaTime) {
    Super::Tick(DeltaTime);
    AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair() const {
    if (!GetControlledTank()) { return; }

    FVector HitLocation;
    if (GetSightRayHitLocation(HitLocation)) {
        UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *(HitLocation.ToString()));
    }

    return;
}

bool ATankPlayerController::GetSightRayHitLocation(FVector& HitLocation) const {
    int32 ViewPortSizeX, ViewPortSizeY;
    GetViewportSize(ViewPortSizeX, ViewPortSizeY);

    auto ScreenLocation = FVector2D(ViewPortSizeX * CrosshairXLocation, ViewPortSizeY * CrosshairYLocation);

    FVector LookDirection;
    if (GetLookDirection(ScreenLocation, LookDirection)) {
        return GetLookVectorHitLocation(LookDirection, HitLocation);
    }

    return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const {
    FVector CameraWorldLocation;
    return DeprojectScreenPositionToWorld(
        ScreenLocation.X,
        ScreenLocation.Y,
        CameraWorldLocation,
        LookDirection
    );
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
    FHitResult HitResult;
    auto CameraLocation = PlayerCameraManager->GetCameraLocation();
    auto TargetLocation = CameraLocation + (LookDirection * LineTraceRange);

    if (GetWorld()->LineTraceSingleByChannel(
        HitResult,
        CameraLocation,
        TargetLocation,
        ECollisionChannel::ECC_Visibility
    )) {
        HitLocation = HitResult.Location;
        return true;
    }

    HitLocation = FVector(0.f);
    return false;
}
