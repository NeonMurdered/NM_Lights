// config.bin - 17:17:53 06/27/22, generated in 0.00 seconds
// Generated by unRap v1.06 by Kegetys
// Separate rootclasses: Disabled, Automatic comments: Enabled

class CfgPatches {
	class NeonM_Lights {
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};

class CfgMods {
	class NeonM_Lights {
		dir = "NeonM_Lights";
		picture = "";
		action = "";
		hideName = 1;
		hidePicture = 1;
		name = "NeonM_Lights";
		credits = "NeonMurder";
		author = "NeonMurder";
		authorID = 76561198102181067;
		version = 0.1;
		extra = 0;
		type = "mod";
		dependencies[] = {"World"};
		
		class defs {
			class worldScriptModule {
				value = "";
				files[] = {"NeonM_Lights/Scripts/4_World"};
			};
		};
	};
};