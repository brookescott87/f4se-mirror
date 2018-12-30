#include "Options.h"

Options::Options()
	:m_launchCS(false)
	,m_setPriority(false)
	,m_priority(0)
	,m_crcOnly(false)
	,m_optionsOnly(false)
	,m_debugWait(false)
	,m_waitForClose(false)
	,m_verbose(false)
	,m_moduleInfo(false)
	,m_skipLauncher(true)
	,m_launchSteam(false)
	,m_noTimeout(false)
	,m_forceSteamLoader(false)
	,m_affinity(0)
{
	//
}

Options::~Options()
{
	//
}

// disable "switch statement contains 'default' but no 'case' labels"
#pragma warning (push)
#pragma warning (disable : 4065)

bool Options::Read(int argc, char ** argv)
{
	if(argc >= 1)
	{
		// remove app name
		argc--;
		argv++;

		int	freeArgCount = 0;

		while(argc > 0)
		{
			char	* arg = *argv++;
			argc--;

			if(arg[0] == '-')
			{
				// switch
				arg++;

				if(!_stricmp(arg, "editor"))
				{
					m_launchCS = true;
				}
				else if(!_stricmp(arg, "priority"))
				{
					if(argc >= 1)
					{
						arg = *argv++;
						argc--;

						m_setPriority = true;

						if(!_stricmp(arg, "above_normal"))
						{
							m_priority = ABOVE_NORMAL_PRIORITY_CLASS;
						}
						else if(!_stricmp(arg, "below_normal"))
						{
							m_priority = BELOW_NORMAL_PRIORITY_CLASS;
						}
						else if(!_stricmp(arg, "high"))
						{
							m_priority = HIGH_PRIORITY_CLASS;
						}
						else if(!_stricmp(arg, "idle"))
						{
							m_priority = IDLE_PRIORITY_CLASS;
						}
						else if(!_stricmp(arg, "normal"))
						{
							m_priority = NORMAL_PRIORITY_CLASS;
						}
						else if(!_stricmp(arg, "realtime"))
						{
							m_priority = REALTIME_PRIORITY_CLASS;
						}
						else
						{
							m_setPriority = false;

							_ERROR("couldn't read priority argument (%s)", arg);
							return false;
						}
					}
					else
					{
						_ERROR("priority not specified");
						return false;
					}
				}
				else if(!_stricmp(arg, "altexe"))
				{
					if(argc >= 1)
					{
						m_altEXE = *argv++;
						argc--;
					}
					else
					{
						_ERROR("exe path not specified");
						return false;
					}
				}
				else if(!_stricmp(arg, "altdll"))
				{
					if(argc >= 1)
					{
						m_altDLL = *argv++;
						argc--;
					}
					else
					{
						_ERROR("dll path not specified");
						return false;
					}
				}
                else if (!_stricmp(arg, "plugindir"))
                {
                    if (argc >= 1)
                    {
                        m_pluginDir = *argv++;
                        argc--;
                    }
                    else
                    {
                        _ERROR("plugindir not specified");
                        return false;
                    }
                }
                else if (!_stricmp(arg, "debugwait"))
				{
					m_debugWait = true;
				}
				else if(!_stricmp(arg, "crconly"))
				{
					m_crcOnly = true;
				}
				else if(!_stricmp(arg, "h") || !_stricmp(arg, "help"))
				{
					m_optionsOnly = true;
				}
				else if(!_stricmp(arg, "waitforclose"))
				{
					m_waitForClose = true;
				}
				else if(!_stricmp(arg, "v"))
				{
					m_verbose = true;
				}
				else if(!_stricmp(arg, "minfo"))
				{
					m_moduleInfo = true;
				}
				else if(!_stricmp(arg, "noskiplauncher"))
				{
					m_skipLauncher = false;
				}
				else if(!_stricmp(arg, "launchsteam"))
				{
					m_launchSteam = true;
				}
				else if(!_stricmp(arg, "notimeout"))
				{
					m_noTimeout = true;
				}
				else if(!_stricmp(arg, "affinity"))
				{
					if(argc >= 1)
					{
						const char	* maskStr = *argv++;
						argc--;

						if(sscanf_s(maskStr, "%I64i", &m_affinity) != 1)
						{
							_ERROR("couldn't read affinity mask as an integer (%s)", maskStr);
							return false;
						}
					}
					else
					{
						_ERROR("affinity mask not specified");
						return false;
					}
				}
				else if(!_stricmp(arg, "forcesteamloader"))
				{
					m_forceSteamLoader = true;
				}
				else
				{
					_ERROR("unknown switch (%s)", arg);
					return false;
				}
			}
			else
			{
				// free arg

				switch(freeArgCount)
				{
				default:
					_ERROR("too many free args (%s)", arg);
					return false;
				}
			}
		}
	}

	return Verify();
}

#pragma warning (pop)

bool Options::EnvSave(LPCSTR envname, int argc, char **argv)
{
	std::string cmdline;
	int i;

	for (i = 0; i < argc; ++i) {
		cmdline += argv[i];
		cmdline += "\n";
	}
	return (bool)SetEnvironmentVariableA(envname, cmdline.c_str());
}

bool Options::EnvRestore(LPCSTR envname)
{
	int argc;
	char *argv[256];
	char cbCmdLine[32768];
	LPSTR lpChr, lpszArg;

	if (GetEnvironmentVariableA(envname, cbCmdLine, sizeof(cbCmdLine)) > sizeof(cbCmdLine))
		return false;
	memset(argv, 0, sizeof(argv));

	for (lpChr = lpszArg = cbCmdLine, argc = 0; *lpChr; ++lpChr) {
		if (*lpChr == '\n') {
			*lpChr = '\0';
			argv[argc++] = lpszArg;
			lpszArg = lpChr + 1;
		}
	}

	bool bResult = Read(argc, argv);

#ifdef _DEBUG
	while (lpChr-- > cbCmdLine)
		if (*lpChr == '\0')
			*lpChr = ' ';

	_MESSAGE("%s: %s", envname, cbCmdLine);
#endif
	return bResult;
}

void Options::PrintUsage(void)
{
	gLog.SetPrintLevel(IDebugLog::kLevel_VerboseMessage);

	_MESSAGE("usage: f4se_loader [options]");
	_MESSAGE("");
	_MESSAGE("options:");
	_MESSAGE("  -h, -help - print this options list");
	_MESSAGE("  -editor - launch the construction set");
	_MESSAGE("  -priority <level> - set the launched program\'s priority");
	_MESSAGE("    above_normal");
	_MESSAGE("    below_normal");
	_MESSAGE("    high");
	_MESSAGE("    idle");
	_MESSAGE("    normal");
	_MESSAGE("    realtime");
	_MESSAGE("  -altexe <path> - set alternate exe path");
	_MESSAGE("  -altdll <path> - set alternate dll path");
    _MESSAGE("  -plugindir <path> - set alternate plugin dir");
    _MESSAGE("  -debugwait - wait for the debugger after loading dll");
	_MESSAGE("  -crconly - just identify the EXE, don't launch anything");
	_MESSAGE("  -waitforclose - wait for the launched program to close");
	_MESSAGE("  -v - print verbose messages to the console");
	_MESSAGE("  -minfo - log information about the DLLs loaded in to the target process");
	_MESSAGE("  -noskiplauncher - does not skip the default Bethesda launcher window");
	_MESSAGE("                    note: specifying this option may cause compatibility problems");
	_MESSAGE("  -launchsteam - attempt to launch steam if it is not running");
	_MESSAGE("  -affinity <mask> - set the processor affinity mask");
	_MESSAGE("  -forcesteamloader - override exe type detection and use steam loader");
}

bool Options::Verify(void)
{
	// nothing to verify currently

	return true;
}
