class RTN_ModuleRegistry : RTN_IService
{
	protected ref array<ref RTN_IModule> m_Modules;
	protected bool m_Inited;

	void RTN_ModuleRegistry()
	{
		m_Modules = new array<ref RTN_IModule>();
	}

	bool Register(RTN_IModule module)
	{
		if (!module) return false;

		string name = module.GetName();
		if (!name) return false;

		foreach (RTN_IModule m : m_Modules)
			if (m && m.GetName() == name)
				return false;

		m_Modules.Insert(module);

		if (m_Inited)
			module.OnInit();

		return true;
	}

	void MarkInited() { m_Inited = true; }

	array<ref RTN_IModule> GetAll()
	{
		return m_Modules;
	}
}