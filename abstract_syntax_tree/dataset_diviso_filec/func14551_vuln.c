	CmdResult HandleLocal(LocalUser* user, const Params& parameters) CXX11_OVERRIDE
	{
		size_t origin = parameters.size() > 1 ? 1 : 0;
		if (parameters[origin].empty())
		{
			user->WriteNumeric(ERR_NOORIGIN, "STR");
			return CMD_FAILURE;
		}

		ClientProtocol::Messages::Pong pong(parameters[0], origin ? parameters[1] : "");
		user->Send(ServerInstance->GetRFCEvents().pong, pong);
		return CMD_SUCCESS;
	}