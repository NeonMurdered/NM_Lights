class NM_KeroseneLamp extends NM_Kerosene_Base
{
	private const string GAS_LIGHT_MATERIAL_ON 		= "dz\\gear\\cooking\\data\\GasLightOn.rvmat";
    private const string GAS_LIGHT_MATERIAL_OFF 	= "dz\\data\\data\\default.rvmat";
	protected const string FLAME_BUTANE_ON 			= "dz\\gear\\cooking\\data\\flame_butane_ca.paa";
	protected const string FLAME_BUTANE_OFF 		= "";
	
	void NM_KeroseneLamp()
	{
		OnWorkStart();
		
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) 
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitSound, 1500, false); //Включение звука, для отключения закоментируйте данную строку
			m_KeroseneLight = KeroseneLampLight.Cast( ScriptedLightBase.CreateLight( KeroseneLampLight, "0 0 0") );
			m_KeroseneLight.AttachOnMemoryPoint(this, "light");
		}
	}
	
	void ~NM_KeroseneLamp()
	{
		OnWorkStop();
		SoundBurningStop();
		
		if (m_KeroseneLight)
			m_KeroseneLight.FadeOut();

		m_KeroseneLight = NULL;
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

class KeroseneLampLight extends PointLightBase
{
	void KeroseneLampLight()
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