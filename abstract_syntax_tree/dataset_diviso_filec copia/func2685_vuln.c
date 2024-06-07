const char *string_of_NPPVariable(int variable)
{
  const char *str;

  switch (variable) {

	_(NPPVpluginNameString);
	_(NPPVpluginDescriptionString);
	_(NPPVpluginWindowBool);
	_(NPPVpluginTransparentBool);
	_(NPPVjavaClass);
	_(NPPVpluginWindowSize);
	_(NPPVpluginTimerInterval);
	_(NPPVpluginScriptableInstance);
	_(NPPVpluginScriptableIID);
	_(NPPVjavascriptPushCallerBool);
	_(NPPVpluginKeepLibraryInMemory);
	_(NPPVpluginNeedsXEmbed);
	_(NPPVpluginScriptableNPObject);
	_(NPPVformValue);
#undef _
  default:
	switch (variable & 0xff) {

	  _(10, NPPVpluginScriptableInstance);
#undef _
	default:
	  str = "STR";
	  break;
	}
	break;
  }

  return str;
}