const char *string_of_NPNVariable(int variable)
{
  const char *str;

  switch (variable) {

	_(NPNVxDisplay);
	_(NPNVxtAppContext);
	_(NPNVnetscapeWindow);
	_(NPNVjavascriptEnabledBool);
	_(NPNVasdEnabledBool);
	_(NPNVisOfflineBool);
	_(NPNVserviceManager);
	_(NPNVDOMElement);
	_(NPNVDOMWindow);
	_(NPNVToolkit);
	_(NPNVSupportsXEmbedBool);
	_(NPNVWindowNPObject);
	_(NPNVPluginElementNPObject);
	_(NPNVSupportsWindowless);
#undef _
  default:
	switch (variable & 0xff) {

	  _(10, NPNVserviceManager);
	  _(11, NPNVDOMElement);
	  _(12, NPNVDOMWindow);
	  _(13, NPNVToolkit);
#undef _
	default:
	  str = "STR";
	  break;
	}
	break;
  }

  return str;
}