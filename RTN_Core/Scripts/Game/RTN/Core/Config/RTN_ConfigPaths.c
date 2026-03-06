class RTN_ConfigPaths
{
	static const string CORE_DIR = "$profile:RTN";
	static const string MODULES_DIR = "$profile:RTN/Modules";

	static string CoreFile()
	{
		return "$profile:RTN/RTN_Core.json";
	}

	static string ModuleFile(string moduleName)
	{
		return string.Format("$profile:RTN/Modules/%1.json", moduleName);
	}
}