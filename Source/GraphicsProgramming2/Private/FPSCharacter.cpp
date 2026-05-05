// Fill out your copyright notice in the Description page of Project Settings.

#include "FPSCharacter.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AFPSCharacter::AFPSCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// This handles creating the rules of the Camera and setting it's state in the editor manually. If we didn't have this, we would have to add the camera component in the editor and set up all of its properties manually, which is more time consuming and error prone. By doing it in code, we can ensure that the camera is always set up correctly and consistently across all instances of the character.
	if (!FPSCameraComponent) // This if check quickly ensures we only create a FPSCameraComponent if we DO NOT have one already. This is important because the constructor can be called multiple times in the editor when we make changes to the class, and we don't want to create multiple camera components if we already have one. This is similar to how we would check if a component already exists in Unity before adding it, but with more options for when the component can be created and where it can be created from.
	{
		FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera")); // Very similar to AddComponent/CreateObject/CreateComponent in Unity, but with more options for when the component can be created and where it can be created from
		FPSCameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent())); // Similar to setting the parent of a transform in Unity, but with more options for how the attachment works
		FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight)); // Similar to setting the local position of a transform in Unity, but with more options for how the location is set
		FPSCameraComponent->bUsePawnControlRotation = true; // Similar to setting the "Use Local Rotation" option of a camera in Unity, but with more options for how the rotation is used
	}

	if (!FPSMeshComponent)
	{
		FPSMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FirstPersonMesh"));
		FPSMeshComponent->SetupAttachment(FPSCameraComponent); // Similar to setting the parent of a transform in Unity, but with more options for how the attachment works
		FPSMeshComponent->SetOnlyOwnerSee(true); // Similar to setting the "Culling Mask" of a camera in Unity, but with more options for how the visibility is set
		FPSMeshComponent->bCastDynamicShadow = false; // Similar to setting the "Cast Shadows" option of a mesh renderer in Unity, but with more options for how the shadows are cast
		FPSMeshComponent->CastShadow = false; // Similar to setting the "Cast Shadows" option of a mesh renderer in Unity, but with more options for how the shadows are cast
	}

	GetMesh()->SetOwnerNoSee(true); // Similar to setting the "Culling Mask" of a camera in Unity, but with more options for how the visibility is set

	UE_LOG(LogTemp, Warning, TEXT("FPSCharacter Constructor Called"));
}

// Called when the game starts or when spawned
void AFPSCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if(APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if(PlayerMappingContext)
		{
			UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
			if(Subsystem)
			{
				Subsystem->AddMappingContext(PlayerMappingContext, 0);
			}
		}
	}
}

// Called every frame
void AFPSCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AFPSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if(UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if(MoveAction)
		{
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Move);
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AFPSCharacter::Look);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AFPSCharacter::StartJump);
			EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFPSCharacter::EndJump);
			EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &AFPSCharacter::Fire);
		}
	}
}

void AFPSCharacter::Move(const FInputActionValue& Value)
{
	const FVector2D MovementVector = Value.Get<FVector2D>();
	AddMovementInput(GetActorForwardVector(), MovementVector.Y);
	AddMovementInput(GetActorRightVector(), MovementVector.X);
}

void AFPSCharacter::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	AddControllerPitchInput(LookAxisVector.Y);
	AddControllerYawInput(LookAxisVector.X);
}

void AFPSCharacter::StartJump()
{
	bPressedJump = true;
}

void AFPSCharacter::EndJump()
{
	bPressedJump = false;
}

void AFPSCharacter::Fire()
{
	if (!ProjectileClass) return;

	// Init relevant infomration for where the projectile will be

	FVector CameraLocation;
	FRotator CameraRotation;
	GetActorEyesViewPoint(CameraLocation, CameraRotation);

	MuzzleOffset.Set(100.0f, 0.0f, 0.0f);

	FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);

	FRotator MuzzleRotation = CameraRotation;
	MuzzleRotation.Pitch += 10.0f;

	// Start of spawning the projectile

	UWorld* World = GetWorld();
	if (!World)  return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();

	// Unity Instantiate

	AFPSProjectile* Projectile = World->SpawnActor<AFPSProjectile>(ProjectileClass, MuzzleLocation, MuzzleRotation, SpawnParams);
	if (!Projectile) return;

	// Launch spawned projectile in the camera rotation

	FVector LaunchDirection = MuzzleRotation.Vector();
	Projectile->FireInDirection(LaunchDirection);
}
