using UnrealBuildTool;
using System.Collections.Generic;

public class ARPG_PROTOTarget : TargetRules
{
	public ARPG_PROTOTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ARPG_PROTO" } );
	}
}
