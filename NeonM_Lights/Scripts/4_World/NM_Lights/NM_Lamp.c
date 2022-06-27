class NM_Lamp extends NM_Lights_Base
{
	void NM_Lamp()
	{
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
		{
			m_Light = LampLight.Cast( ScriptedLightBase.CreateLight(LampLight, "0 0 0", 0) );
			m_Light.AttachOnMemoryPoint(this, "beamStart", "beamEnd");
			m_Light.SetIntensity( 1, 0 );
		}
	}
	
	void ~NM_Lamp()
	{
		if (m_Light)
			m_Light.FadeOut();
			
		m_Light = NULL;
	}
}

class LampLight extends SpotLightBase
{
	private static float m_DefaultBrightness = 0.75;
	private static float m_DefaultRadius = 40;
	
	void LampLight()
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
