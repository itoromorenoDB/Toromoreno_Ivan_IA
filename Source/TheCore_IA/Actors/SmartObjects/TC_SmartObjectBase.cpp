#include "TC_SmartObjectBase.h"
#include "Components/ArrowComponent.h"
#include "Components/BillboardComponent.h"

ATC_SmartObjectBase::ATC_SmartObjectBase() : Super()
{
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	BillboardComponent = CreateDefaultSubobject<UBillboardComponent>(TEXT("BillboardComponent"));
	ArrowComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow Component"));

	ArrowComponent->SetupAttachment(RootComponent);
	BillboardComponent->SetupAttachment(RootComponent);
}
