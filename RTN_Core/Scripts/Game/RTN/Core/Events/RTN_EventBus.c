class RTN_EventBus : RTN_IService
{
	protected ref map<string, ref array<ref RTN_IEventListener>> m_Listeners;

	void RTN_EventBus()
	{
		m_Listeners = new map<string, ref array<ref RTN_IEventListener>>();
	}

	void Subscribe(string eventName, RTN_IEventListener listener)
	{
		if (!eventName || !listener) return;

		if (!m_Listeners.Contains(eventName))
			m_Listeners.Set(eventName, new array<ref RTN_IEventListener>());

		m_Listeners.Get(eventName).Insert(listener);
	}

	void Publish(RTN_EventBase e)
	{
		if (!e) return;

		string name = e.GetName();
		if (!m_Listeners.Contains(name)) return;

		array<ref RTN_IEventListener> list = m_Listeners.Get(name);
		foreach (RTN_IEventListener l : list)
		{
			if (l)
				l.OnEvent(e);
		}
	}
}