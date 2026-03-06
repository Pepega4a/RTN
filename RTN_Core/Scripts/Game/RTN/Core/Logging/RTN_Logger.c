class RTN_Logger : RTN_IService
{
	protected RTN_LogLevel m_Level = RTN_LogLevel.INFO;

	void SetLevel(int levelInt)
	{
		// безопасно приводим int -> enum
		if (levelInt < RTN_LogLevel.TRACE) levelInt = RTN_LogLevel.TRACE;
		if (levelInt > RTN_LogLevel.ERROR) levelInt = RTN_LogLevel.ERROR;

		m_Level = levelInt;
	}

	protected bool Allow(RTN_LogLevel lvl)
	{
		return lvl >= m_Level;
	}

	void Log(RTN_LogLevel lvl, string category, string msg)
	{
		if (!Allow(lvl))
			return;

		string lvlStr = "INFO";
		switch (lvl)
		{
			case RTN_LogLevel.TRACE: lvlStr = "TRACE"; break;
			case RTN_LogLevel.DEBUG: lvlStr = "DEBUG"; break;
			case RTN_LogLevel.INFO:  lvlStr = "INFO";  break;
			case RTN_LogLevel.WARN:  lvlStr = "WARN";  break;
			case RTN_LogLevel.ERROR: lvlStr = "ERROR"; break;
		}

		Print(string.Format("[RTN][%1][%2] %3", category, lvlStr, msg));
	}

	void Trace(string category, string msg) { Log(RTN_LogLevel.TRACE, category, msg); }
	void Debug(string category, string msg) { Log(RTN_LogLevel.DEBUG, category, msg); }
	void Info(string category, string msg)  { Log(RTN_LogLevel.INFO,  category, msg); }
	void Warn(string category, string msg)  { Log(RTN_LogLevel.WARN,  category, msg); }
	void Error(string category, string msg) { Log(RTN_LogLevel.ERROR, category, msg); }
}