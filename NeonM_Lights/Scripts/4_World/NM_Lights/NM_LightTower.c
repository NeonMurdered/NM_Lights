class NM_LightTower extends NM_Lights_Base
{
	void NM_LightTower()
	{
		OnInit(); //Включение дыма, для отключения закоментируйте данную строку
		
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
		{
			GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitSound, 1500, false); //Включение звука, для отключения закоментируйте данную строку
			
			m_TowerLight = TowerLight.Cast( ScriptedLightBase.CreateLight(TowerLight, "0 0 0", 0) );
			m_TowerLight.AttachOnMemoryPoint(this, "beamStart", "beamEnd");
			m_TowerLight.SetIntensity( 1, 0 );
			
			m_TowerLight2 = TowerLight2.Cast( ScriptedLightBase.CreateLight(TowerLight2, "0 0 0", 0) );
			m_TowerLight2.AttachOnMemoryPoint(this, "beamStart2", "beamEnd2");
			m_TowerLight2.SetIntensity( 1, 0 );
			
			m_TowerLight3 = TowerLight3.Cast( ScriptedLightBase.CreateLight(TowerLight3, "0 0 0", 0) );
			m_TowerLight3.AttachOnMemoryPoint(this, "beamStart3", "beamEnd3");
			m_TowerLight3.SetIntensity( 1, 0 );
			
			m_TowerLight4 = TowerLight4.Cast( ScriptedLightBase.CreateLight(TowerLight4, "0 0 0", 0) );
			m_TowerLight4.AttachOnMemoryPoint(this, "beamStart4", "beamEnd4");
			m_TowerLight4.SetIntensity( 1, 0 );
		}
	}
	
	void ~NM_LightTower()
	{
		SoundGeneratorStop();
		
		if (m_Smoke)
		{
			delete m_Smoke;
		}
		
		if (m_TowerLight)
		{
			m_TowerLight.FadeOut();
		}	
		m_TowerLight = NULL;
		
		if (m_TowerLight2)
		{
			m_TowerLight2.FadeOut();
		}
		m_TowerLight2 = NULL;
		
		if (m_TowerLight3)
		{
			m_TowerLight3.FadeOut();
		}
		m_TowerLight3 = NULL;
		
		if (m_TowerLight4)
		{
			m_TowerLight4.FadeOut();
		}
		m_TowerLight4 = NULL;
	}
	
	void InitSound()
    {
        SoundGeneratorStart();
    }
	
	void OnInit()
	{
		vector local_pos = "0 -0.45 -1";
	    vector local_ori = "90 0 0";
		m_Smoke = new EffGeneratorSmoke();
		SEffectManager.PlayOnObject(m_Smoke, this, local_pos, local_ori);
	}
	
	void SoundGeneratorStart()
    {
        if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
        { 
            m_EngineLoop = SEffectManager.PlaySoundOnObject( LOOP_SOUND, this, 0.2, 0.2, true );
        }
    }
	
	void SoundGeneratorStop()
    {
        if ( GetGame() && (!GetGame().IsServer()  ||  !GetGame().IsMultiplayer()))
        {
            if (m_EngineLoop)
            {
				StopSoundSet( m_EngineLoop );
			}
        }
    }	
}

class TowerLight extends SpotLightBase
{
	private static float m_DefaultBrightness = 0.75;
	private static float m_DefaultRadius = 40;
	
	void TowerLight()
	{
		SetVisibleDuringDaylight(false);
		SetRadiusTo(18);
		SetSpotLightAngle(360);
		SetCastShadow(true);
		SetBrightnessTo(0.10);
		SetFadeOutTime(0.15);
		SetAmbientColor(1.0, 0.9, 0.8);
		SetDiffuseColor(239,109,44);
	}
	
	void SetIntensity( float coef, float time )
	{
		FadeBrightnessTo(0.10 * coef, time); //Яркость
		FadeRadiusTo(40 * coef, time); //Радиус освещения
	}
}

class TowerLight2 extends TowerLight
{

}

class TowerLight3 extends TowerLight
{

}

class TowerLight4 extends TowerLight
{

}
