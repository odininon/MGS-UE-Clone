// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "MetalGearSolidCharacter.generated.h"


UCLASS(config=Game)
class AMetalGearSolidCharacter : public ACharacter
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* TiltedCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TiltedFollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* TopDownCameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownFollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FirstPersonCamera;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* FirstPersonLookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* AimAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* CrouchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true", ClampMin = 0.f))
	float FirstPersonLookTurnSpeed = 0.1f;

public:
	AMetalGearSolidCharacter();

	bool bIsCrawling = false;
	bool bIsCrouching = false;

	bool bMovementPressed = false;
	bool bCrouchingPressed = false;
	bool bFirstPersonLookPressed = false;
	bool bAimingPressed = false;

protected:
	/** Called for movement input */
	void BeginMovement(const FInputActionValue& Value);
	void StopMovement(const FInputActionValue& Value);
	
	void BeginFirstPersonLook(const FInputActionValue& Value);
	void StopFirstPersonLook(const FInputActionValue& Value);

	void BeginAiming(const FInputActionValue& Value);
	void StopAiming(const FInputActionValue& Value);

	void BeginCrouching(const FInputActionValue& Value);
	void StopCrouching(const FInputActionValue& Value);

protected:
	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaSeconds) override;
	
	// To add mapping context
	virtual void BeginPlay();

private:
	bool IsTiltedCameraObscured() const;

public:
	FORCEINLINE class USpringArmComponent* GetTiltedCameraBoom() const { return TiltedCameraBoom; }
	FORCEINLINE class UCameraComponent* GetTiltedFollowCamera() const { return TiltedFollowCamera; }
	FORCEINLINE class USpringArmComponent* GetTopDownCameraBoom() const { return TopDownCameraBoom; }
	FORCEINLINE class UCameraComponent* GetTopDownFollowCamera() const { return TopDownFollowCamera; }
};
