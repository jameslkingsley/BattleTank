#pragma once

#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController {
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation = 0.5f;

    UPROPERTY(EditAnywhere)
    float CrosshairYLocation = 0.3333f;

    UPROPERTY(EditAnywhere)
    float LineTraceRange = 100000.0f;

    virtual void BeginPlay() override;
    virtual void Tick(float) override;

    ATank* GetControlledTank() const;
    void AimTowardsCrosshair() const;
    bool GetSightRayHitLocation(FVector&) const;
    bool GetLookDirection(FVector2D, FVector&) const;
    bool GetLookVectorHitLocation(FVector, FVector&) const;
};
