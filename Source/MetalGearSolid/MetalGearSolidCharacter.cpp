#include "MetalGearSolidCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "MGSInventoryComponent.h"
#include "MGSPlayerController.h"
#include "UI/MGSHUDUserWidget.h"

AMetalGearSolidCharacter::AMetalGearSolidCharacter()
{
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f);

	GetCharacterMovement()->JumpZVelocity = 700.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;

	TiltedCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("TiltedCameraBoom"));
	TiltedCameraBoom->SetupAttachment(RootComponent);
	TiltedCameraBoom->TargetArmLength = 800.0f;
	TiltedCameraBoom->bUsePawnControlRotation = false;
	TiltedCameraBoom->bInheritPitch = false;
	TiltedCameraBoom->bInheritRoll = false;
	TiltedCameraBoom->bInheritYaw = false;

	TiltedFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TiltedFollowCamera"));
	TiltedFollowCamera->SetupAttachment(TiltedCameraBoom, USpringArmComponent::SocketName);
	TiltedFollowCamera->bUsePawnControlRotation = false;

	FirstPersonCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	FirstPersonCamera->SetupAttachment(RootComponent);
	FirstPersonCamera->bUsePawnControlRotation = false;

	TopDownCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("TopDownCameraBoom"));
	TopDownCameraBoom->SetupAttachment(RootComponent);
	TopDownCameraBoom->TargetArmLength = 800.0f;
	TopDownCameraBoom->bUsePawnControlRotation = false;
	TopDownCameraBoom->bInheritPitch = false;
	TopDownCameraBoom->bInheritRoll = false;
	TopDownCameraBoom->bInheritYaw = false;

	TopDownFollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownFollowCamera"));
	TopDownFollowCamera->SetupAttachment(TopDownCameraBoom, USpringArmComponent::SocketName);
	TopDownFollowCamera->bUsePawnControlRotation = false;

	InventoryComponent = CreateDefaultSubobject<UMGSInventoryComponent>(TEXT("Inventory"));
}

void AMetalGearSolidCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (const APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}

	TiltedFollowCamera->SetActive(true);
	TopDownFollowCamera->SetActive(false);
	FirstPersonCamera->SetActive(false);

	if (HudClass)
	{
		AMGSPlayerController* PC = GetController<AMGSPlayerController>();
		Hud = CreateWidget<UMGSHUDUserWidget>(PC, HudClass);
		Hud->AddToPlayerScreen();
		Hud->SetInventory(InventoryComponent);
	}
}

void AMetalGearSolidCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	if (Hud)
	{
		Hud->RemoveFromParent();
		Hud = nullptr;
	}

	Super::EndPlay(EndPlayReason);
}

bool AMetalGearSolidCharacter::IsTiltedCameraObscured() const
{
	const auto Start = GetTiltedFollowCamera()->GetComponentLocation();
	const auto End = GetActorLocation();

	if (FHitResult HitResult; GetWorld()->LineTraceSingleByChannel(HitResult, Start, End, ECC_Visibility))
	{
		return true;
	}

	return false;
}

void AMetalGearSolidCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AMetalGearSolidCharacter::BeginMovement);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Started, this, &AMetalGearSolidCharacter::TriggeredMovement);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Completed, this, &AMetalGearSolidCharacter::StopMovement);

		EnhancedInputComponent->BindAction(FirstPersonLookAction, ETriggerEvent::Triggered, this, &AMetalGearSolidCharacter::BeginFirstPersonLook);
		EnhancedInputComponent->BindAction(FirstPersonLookAction, ETriggerEvent::Completed, this, &AMetalGearSolidCharacter::StopFirstPersonLook);

		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Triggered, this, &AMetalGearSolidCharacter::BeginAiming);
		EnhancedInputComponent->BindAction(AimAction, ETriggerEvent::Completed, this, &AMetalGearSolidCharacter::StopAiming);

		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Triggered, this, &AMetalGearSolidCharacter::BeginCrouching);
		EnhancedInputComponent->BindAction(CrouchAction, ETriggerEvent::Completed, this, &AMetalGearSolidCharacter::StopCrouching);

		EnhancedInputComponent->BindAction(WeaponSelectAction, ETriggerEvent::Started, this, &AMetalGearSolidCharacter::BeginWeaponSelect);
		EnhancedInputComponent->BindAction(WeaponSelectAction, ETriggerEvent::Completed, this, &AMetalGearSolidCharacter::StopWeaponSelect);
	}
}

void AMetalGearSolidCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bFirstPersonLookPressed)
	{
		FirstPersonCamera->SetActive(true);
		TopDownFollowCamera->SetActive(false);
		TiltedFollowCamera->SetActive(false);
	}
	else
	{
		FirstPersonCamera->SetActive(false);
		if (IsTiltedCameraObscured())
		{
			TopDownFollowCamera->SetActive(true);
			TiltedFollowCamera->SetActive(false);
		}
		else
		{
			TiltedFollowCamera->SetActive(true);
			TopDownFollowCamera->SetActive(false);
		}
	}
}


void AMetalGearSolidCharacter::BeginMovement(const FInputActionValue& Value)
{
	if (bWeaponSelectPressed)
	{
		return;
	}
	bMovementPressed = true;
	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		if (bFirstPersonLookPressed)
		{
			const FRotator OldRootRotation = GetRootComponent()->GetComponentRotation();
			const FRotator NewRootRotation{
				OldRootRotation.Pitch, OldRootRotation.Yaw + MovementVector.X, OldRootRotation.Roll
			};
			GetRootComponent()->SetWorldRotation(NewRootRotation);

			const FRotator OldCameraRotation = FirstPersonCamera->GetComponentRotation();
			const FRotator NewCameraRotation{
				FMath::Clamp(OldCameraRotation.Pitch + MovementVector.Y, -45, 45), OldCameraRotation.Yaw,
				OldCameraRotation.Roll
			};
			FirstPersonCamera->SetWorldRotation(NewCameraRotation);
		}
		else if (bAimingPressed && !bCrouchingPressed)
		{
			const auto NewRotation = FVector{MovementVector.Y, MovementVector.X, 0.f}.Rotation();
			GetRootComponent()->SetWorldRotation(NewRotation);
		}
		else
		{
			AddMovementInput(ForwardDirection, MovementVector.Y);
			AddMovementInput(RightDirection, MovementVector.X);
		}
	}
}

void AMetalGearSolidCharacter::TriggeredMovement(const FInputActionValue& Value)
{
	if (!bWeaponSelectPressed)
	{
		return;
	}

	const FVector2D MovementVector = Value.Get<FVector2D>();

	if (Hud)
	{
		Hud->WeaponSelectionIndex(FMath::CeilToInt(MovementVector.X));
	}
}

void AMetalGearSolidCharacter::StopMovement(const FInputActionValue& Value)
{
	bMovementPressed = false;
}

void AMetalGearSolidCharacter::BeginFirstPersonLook(const FInputActionValue& Value)
{
	if (bAimingPressed)
	{
		return;
	}

	GetMesh()->bOwnerNoSee = true;
	bFirstPersonLookPressed = true;
}

void AMetalGearSolidCharacter::StopFirstPersonLook(const FInputActionValue& Value)
{
	GetMesh()->bOwnerNoSee = false;

	const FRotator OldCameraRotation = FirstPersonCamera->GetComponentRotation();
	const FRotator NewCameraRotation{0, OldCameraRotation.Yaw, OldCameraRotation.Roll};
	FirstPersonCamera->SetWorldRotation(NewCameraRotation);

	bFirstPersonLookPressed = false;
}

void AMetalGearSolidCharacter::BeginAiming(const FInputActionValue& Value)
{
	if (bFirstPersonLookPressed)
	{
		return;
	}
	bAimingPressed = true;
}

void AMetalGearSolidCharacter::StopAiming(const FInputActionValue& Value)
{
	bAimingPressed = false;
}

void AMetalGearSolidCharacter::BeginCrouching(const FInputActionValue& Value)
{
	bCrouchingPressed = true;
}

void AMetalGearSolidCharacter::StopCrouching(const FInputActionValue& Value)
{
	bCrouchingPressed = false;
}

void AMetalGearSolidCharacter::BeginWeaponSelect(const FInputActionValue& Value)
{
	bWeaponSelectPressed = true;
	if (Hud)
	{
		Hud->ShowWeaponSelection();
	}
}

void AMetalGearSolidCharacter::StopWeaponSelect(const FInputActionValue& Value)
{
	bWeaponSelectPressed = false;
	if (Hud)
	{
		Hud->HideWeaponSelection();
	}
}
