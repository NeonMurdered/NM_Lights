class NM_CampFire extends NM_Fire_Base
{
	void NM_CampFire()
	{
		StartFireEffect();
		StartHeating();
		
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitSound, 1500, false);
			m_CampfireLight = CampfireLight.Cast( ScriptedLightBase.CreateLight( CampfireLight, "0 0 0" ) );
			m_CampfireLight.AttachOnObject(this, m_ParticleLocalPos + Vector (0,-1,0.5));

			m_UTSSettings 					= new UniversalTemperatureSourceSettings();
			m_UTSSettings.m_UpdateInterval	= TIMER_HEATING_UPDATE_INTERVAL;
			m_UTSSettings.m_Updateable		= true;
			m_UTSSettings.m_TemperatureMin	= 0;
			m_UTSSettings.m_TemperatureMax	= CONST_FIRE_TEMP;
			m_UTSSettings.m_TemperatureCap	= PARAM_MAX_TRANSFERED_TEMPERATURE;
			m_UTSSettings.m_RangeFull		= PARAM_FULL_HEAT_RADIUS;
			m_UTSSettings.m_RangeMax		= PARAM_HEAT_RADIUS;
			
			m_UTSLBonfire 					= new UniversalTemperatureSourceLambdaConstant();
			m_UTSource 						= new UniversalTemperatureSource(this, m_UTSSettings, m_UTSLBonfire);
			m_UTSource.SetActive(true);
		}
	}
	
	void ~NM_CampFire()
	{
		StopFireEffect();
		StopSoundLoop();
		StopHeating();
		
		if (m_CampfireLight)
			m_CampfireLight.FadeOut();

		m_UTSource.SetActive(false);
		m_CampfireLight = NULL;
	}
	
	void InitSound()
    {
        SpawnSoundLoop();
    }
	
	void SpawnSoundLoop()
    {
        if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
        { 
            m_SoundFireLoop = SEffectManager.PlaySoundOnObject( SOUND_FIRE_LIGHT, this, 0.2, 0.2, true );
        }
    }

    void StopSoundLoop()
    {
        if ( GetGame() && (!GetGame().IsServer()  ||  !GetGame().IsMultiplayer()))
        {
            if (m_SoundFireLoop)
            {StopSoundSet( m_SoundFireLoop );}
        }
    }
	
	protected void StartFireEffect()
	{
		PlayParticle( m_ParticleNormalFire,  PARTICLE_NORMAL_FIRE, GetEffectPosition() );
		PlayParticle( m_ParticleNormalSmoke, PARTICLE_NORMAL_SMOKE, GetEffectPosition() );
	}

	protected vector GetEffectPosition()
	{
		return Vector( 0, 0.05, 0 );
	}
	
	protected void StopFireEffect()
	{
		StopSoundSet( m_SoundFireLoop );
		
		if ( m_ParticleNormalSmoke && GetGame() && ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) )
		{
			m_ParticleNormalSmoke.Stop();
			m_ParticleNormalSmoke = NULL;
		}
		
		if ( m_ParticleNormalFire && GetGame() && ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) )
		{
			m_ParticleNormalFire.Stop();
			m_ParticleNormalFire = NULL;
		}
	}
	
	protected void StopHeating()
	{
		m_HeatingTimer.Stop();
		m_HeatingTimer = NULL;
	}
	
	protected void AddWetnessToItem( ItemBase item, float amount )
	{
		float wetness = item.GetWet();
		wetness = wetness + amount;
		wetness = Math.Clamp ( wetness, 0, 1 );	
		item.SetWet( wetness );
	}	
	
	protected void BurnItemsInFireplace()
	{
		CargoBase cargo = GetInventory().GetCargo();
		for ( int i = 0; i < cargo.GetItemCount(); i++ )
		{
			ItemBase item = ItemBase.Cast( cargo.GetItem ( i ) );
			
			AddDamageToItemByFire( item, false );

			if ( ( item.GetHealth("", "Health") <= 0 ) && !( item.IsKindOf( "Grenade_Base" ) ) )
			{
				item.Delete();
			}
			
			AddTemperatureToItemByFire( item );
			
			AddWetnessToItem( item, -PARAM_WET_HEATING_DECREASE_COEF );
		}
	}
	
	protected void AddDamageToItemByFire( ItemBase item, bool can_be_ruined )
	{
		item.DecreaseHealth( PARAM_BURN_DAMAGE_COEF, false );

		if ( item.CanBeCooked() & item.GetHealthLevel() >= GameConstants.STATE_BADLY_DAMAGED )
		{
			Edible_Base edible_item = Edible_Base.Cast( item );
			edible_item.ChangeFoodStage( FoodStageType.BURNED );
		}
	}

	protected void AddTemperatureToItemByFire( ItemBase item )
	{
		if ( item.GetTemperatureMax() >= PARAM_ITEM_HEAT_MIN_TEMP )
		{
			float temperature = item.GetTemperature() + PARAM_ITEM_HEAT_TEMP_INCREASE_COEF;
			temperature = Math.Clamp ( temperature, PARAM_ITEM_HEAT_MIN_TEMP, PARAM_MAX_ITEM_HEAT_TEMP_INCREASE );
			item.SetTemperature( temperature );
		}
	}
	
	protected void StartHeating()
	{
		SetObjectMaterial ( 0, MATERIAL_FIREPLACE_GLOW );
		
		m_HeatingTimer = new Timer ( CALL_CATEGORY_GAMEPLAY );
		m_HeatingTimer.Run ( TIMER_HEATING_UPDATE_INTERVAL, this, "Heating", NULL, true );	
	}

	protected void Heating()
	{
		float temperature = GetTemperature();
		float temperature_modifier = 0;

		BurnItemsInFireplace();
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
	
	protected bool PlayParticle( out Particle particle, int particle_type, vector local_pos )
	{
		if ( !particle && GetGame() && ( !GetGame().IsMultiplayer() || GetGame().IsClient() ) )
		{
			particle = Particle.PlayOnObject( particle_type, this, local_pos );
			
			return true;
		}
		
		return false;
	}
}


class CampfireLight extends PointLightBase
{	
	void CampfireLight()
	{
		SetVisibleDuringDaylight(false);
		SetRadiusTo(30);
		SetBrightnessTo(5.0);
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
};