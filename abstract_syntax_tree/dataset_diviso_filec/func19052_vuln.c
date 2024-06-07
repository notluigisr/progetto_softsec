	Pong(const std::string& cookie, const std::string& server = "")
		: ClientProtocol::Message("STR", ServerInstance->Config->GetServerName())
	{
		PushParamRef(ServerInstance->Config->GetServerName());
		if (!server.empty())
			PushParamRef(server);
		PushParamRef(cookie);
	}