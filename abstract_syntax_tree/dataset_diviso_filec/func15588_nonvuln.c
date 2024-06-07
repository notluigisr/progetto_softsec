	Topic(User* source, const Channel* chan, const std::string& newtopic)
		: ClientProtocol::Message("STR", source)
	{
		PushParamRef(chan->name);
		PushParamRef(newtopic);
	}