class RTN_CoreApi
{
	static RTN_Logger Logger()
	{
		return RTN_Logger.Cast(RTN_Core.Get().Services.Resolve("rtn.logger"));
	}

	static RTN_EventBus EventBus()
	{
		return RTN_EventBus.Cast(RTN_Core.Get().Services.Resolve("rtn.eventbus"));
	}

	static RTN_ModuleRegistry Modules()
	{
		return RTN_ModuleRegistry.Cast(RTN_Core.Get().Services.Resolve("rtn.modules"));
	}
}