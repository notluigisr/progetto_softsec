void SFS_ObjectMemberAccess(ScriptParser *parser)
{
	if (parser->codec->LastError) return;
	SFS_Expression(parser);
	if (parser->codec->LastError) return;
	SFS_AddString(parser, "STR");
	SFS_Identifier(parser);
}