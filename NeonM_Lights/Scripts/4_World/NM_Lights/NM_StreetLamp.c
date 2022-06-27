class NM_StreetLamp extends NM_Lights_Base
{
	void NM_StreetLamp()
	{
		if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() )
		{
			m_StrtLight = StrtLight.Cast( ScriptedLightBase.CreateLight(StrtLight, "0 0 0", 0) );
			m_StrtLight.AttachOnMemoryPoint(this, "beamStart", "beamEnd");
			m_StrtLight.SetIntensity( 1, 0 );
		}
	}
	
	void ~NM_StreetLamp()
	{
		if (m_StrtLight)
			m_StrtLight.FadeOut();
			
		m_StrtLight = NULL;
	}
}

class StrtLight extends SpotLightBase
{
	private static float m_DefaultBrightness = 0.75;
	private static float m_DefaultRadius = 40;
	
	void StrtLight()
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
		FadeBrightnessTo(0.05 * coef, time); //Яркость
		FadeRadiusTo(40 * coef, time); //Радиус освещения
	}
}
