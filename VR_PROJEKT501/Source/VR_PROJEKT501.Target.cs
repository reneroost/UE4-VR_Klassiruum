// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class VR_PROJEKT501Target : TargetRules
{
	public VR_PROJEKT501Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "VR_PROJEKT501" } );
	}
}
