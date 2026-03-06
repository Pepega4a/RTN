class RTN_Core
{
	private static ref RTN_Core s_Instance;

	ref RTN_ServiceRegistry Services;

	static RTN_Core Get()
	{
		if (!s_Instance)
			s_Instance = new RTN_Core();

		return s_Instance;
	}

	// Точка расширения: другие RTN_* моды могут зарегистрировать свои модули
	// через: modded class RTN_Core { override protected void CollectModules(RTN_ModuleRegistry reg) { ... } }
	protected void CollectModules(RTN_ModuleRegistry reg)
	{
	}

	void Init()
	{
		// защита от повторной инициализации
		if (Services)
			return;

		// 1) registry
		Services = new RTN_ServiceRegistry();
		
		// config
		RTN_CoreConfig cfg = new RTN_CoreConfig();
		cfg.Load();
		Services.Register("rtn.config.core", cfg);

		// 2) logger
		RTN_Logger logger = new RTN_Logger();
		Services.Register("rtn.logger", logger);

		logger.SetLevel(cfg.Get().m_LogLevel);

		logger.Info("Core", "RTN_Core initialized");
		logger.Info("Core", "Config path: " + cfg.GetFilePath());
		logger.Info("Core", "LogLevel: " + cfg.Get().m_LogLevel);
		
		// 3) event bus
		RTN_EventBus bus = new RTN_EventBus();
		Services.Register("rtn.eventbus", bus);

		// 4) modules
		RTN_ModuleRegistry modules = new RTN_ModuleRegistry();
		Services.Register("rtn.modules", modules);

		Print("[RTN][Core] Init entered (Print testы)");
		logger.Info("Core", "RTN_Core initialized");

		// 5) дать внешним модам зарегистрировать модули
		CollectModules(modules);

		// 6) init modules
		foreach (RTN_IModule m0 : modules.GetAll())
		{
			if (!cfg.IsModuleEnabled(m0.GetName()))
				continue;
			
			m0.OnInit();
		}
		modules.MarkInited();

		// 7) core initialized event
		bus.Publish(new RTN_EventCoreInitialized());

		// 8) server start
		if (Replication.IsServer())
		{
			logger.Info("Core", "Server start");
			bus.Publish(new RTN_EventServerStarted());

			foreach (RTN_IModule ms : modules.GetAll())
			{
				if(!cfg.IsModuleEnabled(ms.GetName()))
					continue;
				
				ms.OnServerStart();
			}
		}

		// 9) client start
		if (Replication.IsClient())
		{
			logger.Info("Core", "Client start");
			bus.Publish(new RTN_EventClientStarted());

			foreach (RTN_IModule mc : modules.GetAll())
			{
				if(!cfg.IsModuleEnabled(mc.GetName()))
					continue;
				
				mc.OnClientStart();
			}
		}
	}
}