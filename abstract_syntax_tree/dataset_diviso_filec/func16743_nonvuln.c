CModCommand::CModCommand(const CString& sCmd, CModule* pMod, ModCmdFunc func,
                         const CString& sArgs, const CString& sDesc)
    : m_sCmd(sCmd),
      m_pFunc([pMod, func](const CString& sLine) { (pMod->*func)(sLine); }),
      m_Args(sArgs),
      m_Desc(sDesc) {}