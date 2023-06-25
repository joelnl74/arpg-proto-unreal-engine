using UnrealBuildTool;
using System.Collections.Generic;

public class ARPG_PROTOEditorTarget : TargetRules
{
	public ARPG_PROTOEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "ARPG_PROTO" } );
	}
}
