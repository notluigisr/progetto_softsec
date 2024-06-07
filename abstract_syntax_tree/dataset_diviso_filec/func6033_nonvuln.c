DefineViewRules(Oid viewOid, Query *viewParse, bool replace)
{
	
	DefineQueryRewrite(pstrdup(ViewSelectRuleName),
					   viewOid,
					   NULL,
					   CMD_SELECT,
					   true,
					   replace,
					   list_make1(viewParse));

	
}