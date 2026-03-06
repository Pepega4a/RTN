class RTN_ModuleConfigBase : RTN_IService
{
	// имя модуля (например "RTN_Economy")
	protected string m_ModuleName;

	void RTN_ModuleConfigBase(string moduleName)
	{
		m_ModuleName = moduleName;
	}

	string GetModuleName()
	{
		return m_ModuleName;
	}

	string GetFilePath()
	{
		return RTN_ConfigPaths.ModuleFile(m_ModuleName);
	}

	protected void EnsureDir()
	{
		FileIO.MakeDirectory(RTN_ConfigPaths.MODULES_DIR);
	}

	// Каждый модуль реализует сам: какие поля грузим/сохраняем
	protected bool ReadFromJson(SCR_JsonLoadContext ctx) { return true; }
	protected bool WriteToJson(SCR_JsonSaveContext ctx) { return true; }

	bool Load()
	{
		EnsureDir();

		string path = GetFilePath();
		if (!FileIO.FileExists(path))
			return Save();

		SCR_JsonLoadContext ctx = new SCR_JsonLoadContext();
		if (!ctx.LoadFromFile(path))
			return false;

		return ReadFromJson(ctx);
	}

	bool Save()
	{
		EnsureDir();

		SCR_JsonSaveContext ctx = new SCR_JsonSaveContext();
		if (!WriteToJson(ctx))
			return false;

		return ctx.SaveToFile(GetFilePath());
	}
}