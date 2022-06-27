class NM_KeroseneLamp_2 extends NM_Kerosene_Base
{
	private const string GAS_LIGHT_MATERIAL_ON 		= "dz\\gear\\cooking\\data\\GasLightOn.rvmat";
    private const string GAS_LIGHT_MATERIAL_OFF 	= "dz\\data\\data\\default.rvmat";
	protected const string FLAME_BUTANE_ON 			= "dz\\gear\\cooking\\data\\flame_butane_ca.paa";
	protected const string FLAME_BUTANE_OFF 		= "";
	
	void NM_KeroseneLamp_2()
	{
		OnWorkStart();
		
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) 
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitSound, 1500, false); //Включение звука, для отключения закоментируйте данную строку
			m_KeroseneLight_2 = KeroseneLampLight_2.Cast( ScriptedLightBase.CreateLight( KeroseneLampLight_2, "0 0 0") );
			m_KeroseneLight_2.AttachOnMemoryPoint(this, "light");
		}
	}
	
	void ~NM_KeroseneLamp_2()
	{
		OnWorkStop();
		SoundBurningStop();
		
		if (m_KeroseneLight_2)
			m_KeroseneLight_2.FadeOut();

		m_KeroseneLight_2 = NULL;
	}
	
	void InitSound()
    {
        SoundBurningStart();
    }
	
	override void OnWorkStart()
	{
		SetObjectTexture( 0, FLAME_BUTANE_ON );
		SetObjectMaterial( 0, GAS_LIGHT_MATERIAL_ON );
	}

	override void OnWorkStop()
	{
		SetObjectTexture( 0, FLAME_BUTANE_OFF );
		SetObjectMaterial( 0, GAS_LIGHT_MATERIAL_OFF );
	}
	
	void SoundBurningStart()
    {
        if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
        { 
            m_SoundBurningLoop = SEffectManager.PlaySoundOnObject( SOUND_BURNING, this, 0.2, 0.2, true );
        }
    }
	
	void SoundBurningStop()
    {
        if ( GetGame() && (!GetGame().IsServer()  ||  !GetGame().IsMultiplayer()))
        {
            if (m_SoundBurningLoop)
            {
				StopSoundSet( m_SoundBurningLoop );
			}
        }
    }	
	
	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if (GetHierarchyParent())
		{
			return false;
		}

		return super.CanReceiveItemIntoCargo(item);
	}

	override bool CanLoadItemIntoCargo(EntityAI item)
	{
		if (GetHierarchyParent())
			return false;

		return super.CanLoadItemIntoCargo(item);
	}
	
	override bool CanPutInCargo( EntityAI parent )
    {
        if( !super.CanPutInCargo(parent) ) {return false;}        
        if ( GetNumberOfItems() == 0)
        {
            return false;
        }
        return false;
    }
	
	override bool CanPutIntoHands(EntityAI parent)
    {
        if( !super.CanPutIntoHands( parent ) )
        {
            return false;
        }
        if ( GetNumberOfItems() == 0 )
        {
            return false;
        }
        return false;
    }
}

class KeroseneLampLight_2 extends PointLightBase
{
	void KeroseneLampLight_2()
	{
		SetVisibleDuringDaylight(false);
		SetRadiusTo(15);
		SetBrightnessTo(3.0);
		SetCastShadow(false);
		SetFadeOutTime(1);
		SetDiffuseColor(1.0, 0.45, 0.25);
		SetAmbientColor(1.0, 0.45, 0.25);
		SetFlareVisible(false);
		SetFlickerAmplitude(0.55);
		SetFlickerSpeed(0.75);
		SetDancingShadowsMovementSpeed(0.1);
		SetDancingShadowsAmplitude(0.03);
	}
}