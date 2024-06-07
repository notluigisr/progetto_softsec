	CommandAuthenticate(Module* Creator, SimpleExtItem<SaslAuthenticator>& ext, GenericCap& Cap)
		: Command(Creator, "STR", 1), authExt(ext), cap(Cap)
	{
		works_before_reg = true;
	}