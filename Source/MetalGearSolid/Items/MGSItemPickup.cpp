// Fill out your copyright notice in the Description page of Project Settings.


#include "MGSItemPickup.h"

#include "MGSItem.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "MetalGearSolid/MetalGearSolidCharacter.h"
#include "MetalGearSolid/MGSInventoryComponent.h"

// Sets default values
AMGSItemPickup::AMGSItemPickup()
{
	PrimaryActorTick.bCanEverTick = true;

	DefaultRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Default Root"));
	SetRootComponent(DefaultRoot);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetCollisionProfileName(TEXT("Trigger"));

	TextSphereTrigger = CreateDefaultSubobject<USphereComponent>(TEXT("TextSphereTrigger"));
	TextSphereTrigger->SetupAttachment(RootComponent);
	TextSphereTrigger->SetCollisionProfileName(TEXT("Trigger"));
	TextSphereTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMGSItemPickup::OnTextSphereTriggerBeginOverlap);
	TextSphereTrigger->OnComponentEndOverlap.AddDynamic(this, &AMGSItemPickup::OnTextSphereTriggerEndOverlap);

	PickupTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("PickupTrigger"));
	PickupTrigger->SetCollisionProfileName(TEXT("Trigger"));
	PickupTrigger->OnComponentBeginOverlap.AddDynamic(this, &AMGSItemPickup::OnPickupTriggerBeginOverlap);

	PickupTrigger->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMGSItemPickup::BeginPlay()
{
	Super::BeginPlay();
}

void AMGSItemPickup::OnTextSphereTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                     UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
                                                     bool bBFromSweep, const FHitResult& SweepResult)
{
	if (Item)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Item->ItemDisplayName.ToString());
	}
}

void AMGSItemPickup::OnTextSphereTriggerEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

void AMGSItemPickup::OnPickupTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                 UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bBFromSweep,
                                                 const FHitResult& SweepResult)
{
	const AMetalGearSolidCharacter* Character = Cast<AMetalGearSolidCharacter>(OtherActor);
	if (Character && Item)
	{
		if (Character->InventoryComponent->AddItem(Item))
		{
			Destroy();
		}
	}
}

// Called every frame
void AMGSItemPickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
