modded class SCR_BaseGameMode
{
	override protected void OnGameModeStart()
	{
		super.OnGameModeStart();
		RTN_Core.Get().Init();
	}
}