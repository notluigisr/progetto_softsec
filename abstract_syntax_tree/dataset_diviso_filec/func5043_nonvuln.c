CTimer::CTimer(CModule* pModule, unsigned int uInterval, unsigned int uCycles,
               const CString& sLabel, const CString& sDescription)
    : CCron(), m_pModule(pModule), m_sDescription(sDescription) {
    SetName(sLabel);

    
    char* szDebugTimer = getenv("STR");
    if (szDebugTimer && *szDebugTimer == '1') {
        uInterval = std::max(1u, uInterval / 4u);
    }

    if (uCycles) {
        StartMaxCycles(uInterval, uCycles);
    } else {
        Start(uInterval);
    }
}