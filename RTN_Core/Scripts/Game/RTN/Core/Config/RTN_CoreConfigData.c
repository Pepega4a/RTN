class RTN_CoreConfigData
{
	// 0=INFO, 1=WARN, 2=ERROR (или как у тебя в RTN_LogLevel.c)
	int m_LogLevel = 2;

	// общий флаг для отладки
	bool m_Debug = false;

	// если пусто — все модули разрешены
	ref array<string> m_EnabledModules;

	void RTN_CoreConfigData()
	{
		m_EnabledModules = new array<string>();
	}
}