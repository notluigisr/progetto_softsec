void SFS_ArrayDeref(ScriptParser *parser)
{
	if (parser->codec->LastError) return;
	SFS_Expression(parser);
	SFS_AddString(parser, "STR");
	SFS_CompoundExpression(parser);
	SFS_AddString(parser, "STR");
}