class RTN_ServiceRegistry
{
	protected ref map<string, ref RTN_IService> m_Services;

	void RTN_ServiceRegistry()
	{
		m_Services = new map<string, ref RTN_IService>();
	}

	void Register(string key, RTN_IService service)
	{
		if (!key) return;
		if (!service) return;

		m_Services.Set(key, service);
	}

	RTN_IService Resolve(string key)
	{
		RTN_IService s;
		if (m_Services.Find(key, s))
			return s;

		return null;
	}

	bool Has(string key)
	{
		return m_Services.Contains(key);
	}
}