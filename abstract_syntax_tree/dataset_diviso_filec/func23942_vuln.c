	SilenceMessage(const std::string& mask, const std::string& flags)
		: ClientProtocol::Message("STR")
	{
		PushParam(mask);
		PushParamRef(flags);
	}