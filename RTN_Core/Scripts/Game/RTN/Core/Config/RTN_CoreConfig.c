class RTN_CoreConfig : RTN_IService
{
	protected ref RTN_CoreConfigData m_Data;

	void RTN_CoreConfig()
	{
		m_Data = new RTN_CoreConfigData();
	}

	RTN_CoreConfigData Get()
	{
		return m_Data;
	}

	string GetFilePath()
	{
		return RTN_ConfigPaths.CoreFile();
	}

	bool Load()
	{
		FileIO.MakeDirectory(RTN_ConfigPaths.CORE_DIR);

		string path = RTN_ConfigPaths.CoreFile();

		// нет файла — создаём дефолт
		if (!FileIO.FileExists(path))
			return Save();

		SCR_JsonLoadContext ctx = new SCR_JsonLoadContext();
		if (!ctx.LoadFromFile(path))
			return false;

		int lvl;
		if (ctx.ReadValue("LogLevel", lvl))
			m_Data.m_LogLevel = lvl;

		bool dbg;
		if (ctx.ReadValue("Debug", dbg))
			m_Data.m_Debug = dbg;

		array<string> mods = new array<string>();
		if (ctx.ReadValue("EnabledModules", mods))
			m_Data.m_EnabledModules = mods;

		// safety: если почему-то null
		if (!m_Data.m_EnabledModules)
			m_Data.m_EnabledModules = new array<string>();

		return true;
	}

	bool Save()
	{
		FileIO.MakeDirectory(RTN_ConfigPaths.CORE_DIR);

		SCR_JsonSaveContext ctx = new SCR_JsonSaveContext();
		ctx.WriteValue("LogLevel", m_Data.m_LogLevel);
		ctx.WriteValue("Debug", m_Data.m_Debug);
		ctx.WriteValue("EnabledModules", m_Data.m_EnabledModules);

		return ctx.SaveToFile(RTN_ConfigPaths.CoreFile());
	}

	bool IsModuleEnabled(string moduleName)
	{
		if (!moduleName)
			return false;

		// пусто = всё включено
		if (!m_Data.m_EnabledModules || m_Data.m_EnabledModules.IsEmpty())
			return true;

		foreach (string s : m_Data.m_EnabledModules)
			if (s == moduleName)
				return true;

		return false;
	}
}