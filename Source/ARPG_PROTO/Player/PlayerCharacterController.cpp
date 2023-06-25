#include "ARPG_PROTO/Player/PlayerCharacterController.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "ARPG_PROTO/Interaction/EnemyInterface.h"

APlayerCharacterController::APlayerCharacterController()
{
	bReplicates = true;
}

void APlayerCharacterController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	CursorTrace();
}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();

	check(inputMappingContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(inputMappingContext, 0);

	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);
	SetInputMode(InputModeData);
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(moveAction, ETriggerEvent::Triggered, this, &APlayerCharacterController::Move);
}

void APlayerCharacterController::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator Rotation = GetControlRotation();
	const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(ForwardDirection, InputAxisVector.Y);
		ControlledPawn->AddMovementInput(RightDirection, InputAxisVector.X);
	}
}

void APlayerCharacterController::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility, false, CursorHit);
	
	if (CursorHit.bBlockingHit == false)
	{
		return;
	}

	lastActor = thisActor;
	thisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if (lastActor == nullptr && thisActor == nullptr)
	{
		return;
	}

	if (lastActor != thisActor && thisActor != nullptr && lastActor != nullptr)
	{
		lastActor->UnHighLightActor();
		thisActor->HighLightActor();

		return;
	}

	if (thisActor != nullptr)
	{
		thisActor->HighLightActor();

		return;
	}

	if (lastActor != nullptr)
	{
		lastActor->UnHighLightActor();

		return;
	}


}
