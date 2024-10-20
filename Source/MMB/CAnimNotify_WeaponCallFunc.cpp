#include "CAnimNotify_WeaponCallFunc.h"
#include "IPlayerState.h"

void UCAnimNotify_WeaponCallFunc::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	IIPlayerState* PlayerState = Cast<IIPlayerState>(MeshComp->GetOwner());
	if (PlayerState == nullptr) return;
	if (WeaponType < 1)
	{
		switch (ToCallFunc)
		{
		case(0):	// Throw Staff Effect Forward
			PlayerState->ThrowStaffEffect();
			break;
		case(1):	// Turn To Brute Mode If Brute Gauge Is Enough ( Check Condition In Function )
			PlayerState->TurnBruteMode();
			break;
		case(2):	// Throw Direct Forward
			PlayerState->Ult_ThrowStaffEffectDirect();
			break;
		case(3):	// Jump Init
			PlayerState->Ult_Jump();
			break;
		case(4):	// Punch Ready
			PlayerState->Ult_PunchInit();
			break;
		case(5):	// Airbone
			PlayerState->Ult_Airbone();
			break;
		case(6):	// Land + Deal Damage
			PlayerState->Ult_Land();
			break;
		case(7):
			PlayerState->Ult_HitGround();
			break;
		case(8):	// Backflip
			PlayerState->Ult_Backflip();
			break;
		case(9):	// Sheath Switch Back Socket
			PlayerState->SwitchBruteMode(true);
			break;
		case(10):	// Draw Switch Hand Socket
			PlayerState->SwitchBruteMode(false);
			break;
		}
	}
	else
	{
		switch (ToCallFunc)
		{
		case(0):	// Switch Hand To Temp (Left) / Spawn + Attach Beacon To RHand
			PlayerState->SwitchWeaponHoldingHand(true);
			PlayerState->SpawnAndGraspBeacon();
			break;
		case(1):	// Throw Beacon To Target;
			PlayerState->ThrowBeacon();
		case(2):	// Switch Hand To Normal (Right)
			PlayerState->SwitchWeaponHoldingHand(false);
		default:
			break;
		}
	}
}
