#pragma once

class Options
{
public:
	Options();
	~Options();

	bool	Read(int argc, char ** argv);
	static bool	EnvSave(LPCSTR envname, int argc, char **argv);
	bool	EnvRestore(LPCSTR envname);

	void	PrintUsage(void);

	bool	m_launchCS;

	bool	m_setPriority;
	DWORD	m_priority;

	bool	m_optionsOnly;
	bool	m_crcOnly;
	bool	m_debugWait;
	bool	m_waitForClose;
	bool	m_verbose;
	bool	m_moduleInfo;
	bool	m_skipLauncher;
	bool	m_launchSteam;
	bool	m_noTimeout;
	bool	m_forceSteamLoader;

	UInt64	m_affinity;

	std::string	m_altEXE;
	std::string	m_altDLL;
    std::string m_pluginDir;
	
	std::string m_flags;
private:
	bool	Verify(void);
};

extern Options g_options;
