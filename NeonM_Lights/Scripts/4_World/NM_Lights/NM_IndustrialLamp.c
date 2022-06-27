class NM_IndustrialLamp extends NM_Lights_Base
{
	void NM_IndustrialLamp()
	{
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
		{
			m_IndustrialLight = IndustrialLight.Cast( ScriptedLightBase.CreateLight(IndustrialLight, "0 0 0", 0) );
			m_IndustrialLight.AttachOnMemoryPoint(this, "beamStart", "beamEnd");
			m_IndustrialLight.SetIntensity( 1, 0 );
			
			m_IndustrialLight2 = IndustrialLight2.Cast( ScriptedLightBase.CreateLight(IndustrialLight2, "0 0 0", 0) );
			m_IndustrialLight2.AttachOnMemoryPoint(this, "beamStart2", "beamEnd2");
			m_IndustrialLight2.SetIntensity( 1, 0 );
		}
	}
	
	void ~NM_IndustrialLamp()
	{
		if (m_IndustrialLight)
		{
			m_IndustrialLight.FadeOut();
		}	
		m_IndustrialLight = NULL;
		
		if (m_IndustrialLight2)
		{
			m_IndustrialLight2.FadeOut();
		}
		m_IndustrialLight2 = NULL;
	}
}

class IndustrialLight extends SpotLightBase
{
	private static float m_DefaultBrightness = 0.75;
	private static float m_DefaultRadius = 40;
	
	void IndustrialLight()
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

class IndustrialLight2 extends SpotLightBase
{
	private static float m_DefaultBrightness = 0.75;
	private static float m_DefaultRadius = 40;
	
	void IndustrialLight2()
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
