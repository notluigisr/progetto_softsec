vncProperties::ApplyUserPrefs()
{
	

	
	m_server->EnableFileTransfer(m_pref_EnableFileTransfer);
	m_server->FTUserImpersonation(m_pref_FTUserImpersonation); 
	m_server->Primary(m_pref_Primary);
	m_server->Secondary(m_pref_Secondary);

	m_server->BlankMonitorEnabled(m_pref_EnableBlankMonitor);
	m_server->BlankInputsOnly(m_pref_BlankInputsOnly); 
	m_server->SetDefaultScale(m_pref_DefaultScale);

	
	m_server->SetQuerySetting(m_pref_QuerySetting);
	m_server->SetQueryTimeout(m_pref_QueryTimeout);
	m_server->SetQueryDisableTime(m_pref_QueryDisableTime);
	m_server->SetQueryAccept(m_pref_QueryAccept);
	m_server->setMaxViewerSetting(m_pref_MaxViewerSetting);
	m_server->setMaxViewers(m_pref_MaxViewers);
	m_server->setCollabo(m_pref_Collabo);

	m_server->setFrame(m_pref_Frame);
	m_server->setNotification(m_pref_Notification);
	m_server->setOSD(m_pref_OSD);
	m_server->setNotificationSelection(m_pref_NotificationSelection);

	m_server->SetAutoIdleDisconnectTimeout(m_pref_IdleTimeout);
	m_server->EnableRemoveWallpaper(m_pref_RemoveWallpaper);
	
	m_server->EnableRemoveFontSmoothing(m_pref_RemoveFontSmoothing);
	m_server->EnableRemoveEffects(m_pref_RemoveEffects);

	

	if (!m_pref_SockConnect)
		m_server->SockConnect(m_pref_SockConnect);

	m_server->EnableHTTPConnect(m_pref_HTTPConnect);

	
	if (!m_pref_EnableRemoteInputs)
		m_server->EnableRemoteInputs(m_pref_EnableRemoteInputs);
	if (m_pref_DisableLocalInputs)
		m_server->DisableLocalInputs(m_pref_DisableLocalInputs);
	if (m_pref_EnableJapInput)
		m_server->EnableJapInput(m_pref_EnableJapInput);
	if (m_pref_EnableUnicodeInput)
		m_server->EnableUnicodeInput(m_pref_EnableUnicodeInput);
	if (m_pref_EnableWin8Helper)
		m_server->Win8HelperEnabled(m_pref_EnableWin8Helper);
	m_server->Clearconsole(m_pref_clearconsole);

	
	m_server->SetPassword(m_pref_passwd);
	m_server->SetPassword2(m_pref_passwd2); 

	
	m_server->SetAutoPortSelect(m_pref_AutoPortSelect);
	if (!m_pref_AutoPortSelect)
		
		m_server->SetPorts(m_pref_PortNumber, m_pref_HttpPortNumber); 

	m_server->SockConnect(m_pref_SockConnect);

	
	m_server->EnableRemoteInputs(m_pref_EnableRemoteInputs);
	m_server->SetLockSettings(m_pref_LockSettings);
	m_server->DisableLocalInputs(m_pref_DisableLocalInputs);
	m_server->EnableJapInput(m_pref_EnableJapInput);
	m_server->EnableUnicodeInput(m_pref_EnableUnicodeInput);
	m_server->Win8HelperEnabled(m_pref_EnableWin8Helper);
	m_server->Clearconsole(m_pref_clearconsole);
	
	m_server->EnableDSMPlugin(m_pref_UseDSMPlugin);
	m_server->SetDSMPluginName(m_pref_szDSMPlugin);
	
	
	m_server->SetDSMPluginConfig(m_pref_DSMPluginConfig);

	if (m_server->IsDSMPluginEnabled()) 
		m_server->SetDSMPlugin(false);
}