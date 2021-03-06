#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "Tank.h"

// Sets default values
ATank::ATank() {
    // Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    // No need to protect pointers as added at construction
    TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay() {
    Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(class UInputComponent* InputComponent) {
    Super::SetupPlayerInputComponent(InputComponent);
}

void ATank::AimAt(FVector HitLocation) {
    TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::SetBarrelReference(UTankBarrel* BarrelToSet) {
    TankAimingComponent->SetBarrelReference(BarrelToSet);
}
