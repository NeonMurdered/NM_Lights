class NM_Fire_Base extends ItemBase
{
   protected Particle m_ParticleNormalFire;
	protected Particle m_ParticleNormalSmoke;
	
	const string SOUND_FIRE_LIGHT				= "LightFire_SoundSet";

	const string MATERIAL_FIREPLACE_GLOW 		= "dz\\gear\\cooking\\data\\stoneground.rvmat";

	const float TIMER_HEATING_UPDATE_INTERVAL		= 2;
	const float PARAM_HEAT_RADIUS					   = 8;
	const float PARAM_FULL_HEAT_RADIUS				= 5;
	const float	PARAM_MAX_TRANSFERED_TEMPERATURE	= 30;
	const float CONST_FIRE_TEMP						= 1000;
	
	const float	PARAM_BURN_DAMAGE_COEF				= 5.0;
	const float	PARAM_WET_HEATING_DECREASE_COEF 	= 0.01;
	const float	PARAM_ITEM_HEAT_TEMP_INCREASE_COEF	= 10;		
	const float	PARAM_ITEM_HEAT_MIN_TEMP			= 40;		
	const float PARAM_MAX_ITEM_HEAT_TEMP_INCREASE	= 200;			
   const float PARAM_HEAT_THROUGH_AIR_COEF			= 0.035;	
	
	protected ref Timer m_HeatingTimer;

	protected EffectSound m_SoundFireLoop;
	protected ref UniversalTemperatureSource m_UTSource;
	protected ref UniversalTemperatureSourceSettings m_UTSSettings;
	protected ref UniversalTemperatureSourceLambdaConstant m_UTSLBonfire;

	protected int PARTICLE_NORMAL_FIRE	= ParticleList.CAMP_NORMAL_FIRE;
	protected int PARTICLE_NORMAL_SMOKE	= ParticleList.CAMP_NORMAL_SMOKE;
	
	CampfireLight       m_CampfireLight;
	CampfireLightEmpty  m_CampfireLightEmpty
	
	vector m_ParticleLocalPos;
}
