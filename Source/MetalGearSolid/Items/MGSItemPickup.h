// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MGSItemPickup.generated.h"

UCLASS()
class METALGEARSOLID_API AMGSItemPickup : public AActor
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	class USceneComponent* DefaultRoot = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Mesh, meta= (AllowPrivateAccess = "true"))
	class UMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Triggers, meta= (AllowPrivateAccess = "true"))
	class USphereComponent* TextSphereTrigger;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category= Triggers, meta= (AllowPrivateAccess = "true"))
	class UBoxComponent* PickupTrigger;

	UPROPERTY(EditInstanceOnly, Category= Item, meta= (AllowPrivateAccess = "true"))
	class UMGSItem* Item;

	bool bPlayerInTextArea = false;

public:
	AMGSItemPickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTextSphereTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep,
	                                     const FHitResult& SweepResult);

	UFUNCTION()
	void OnTextSphereTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnPickupTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep,
	                                 const FHitResult& SweepResult);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
