class NM_Torch extends NM_Lights_Base
{
	Particle m_FireParticle;
	vector m_ParticleLocalPos;
	
	const string SOUND_FIRE_LIGHT				= "LightFire_SoundSet";
	
	protected EffectSound m_SoundFireLoop;
	
	void NM_Torch()
	{
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitSound, 1500, false);
            m_ParticleLocalPos = GetParticleLocalPos();
			m_Torch_Light = Torch_Light.Cast( ScriptedLightBase.CreateLight( Torch_Light, "0 0 0" ) );
			m_Torch_Light.AttachOnObject(this, m_ParticleLocalPos + Vector (0,-1,0.5));
            m_FireParticle = Particle.PlayOnObject(ParticleList.TORCH_T1, this, m_ParticleLocalPos, Vector(0,0,0), true);            
		}
	}
	
	void ~NM_Torch()
	{
		StopSoundLoop();
		
		if (m_Torch_Light)
			m_Torch_Light.FadeOut();
		if (m_FireParticle)
			    m_FireParticle.Stop();
			
		m_Torch_Light = NULL;
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
    
    vector GetParticleLocalPos()
    {
        return Vector(0, 0.50, 0);
    }
};

class Torch_Light extends PointLightBase
{	
	void Torch_Light()
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