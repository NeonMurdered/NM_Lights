class NM_Lights_Base extends House
{
	static const string			LOOP_SOUND = "powerGeneratorLoop_SoundSet";
	
	protected EffectSound 		m_EngineLoop;
	ref protected Effect 		m_Smoke;
	
    IndustrialLight   m_IndustrialLight;
	IndustrialLight2  m_IndustrialLight2;
	
	LampLight         m_Light;
	
	StrtLight         m_StrtLight;
	
	Torch_Light       m_Torch_Light;
	
	TowerLight        m_TowerLight;
	TowerLight2       m_TowerLight2;
	TowerLight3       m_TowerLight3;
	TowerLight4       m_TowerLight4;
}
