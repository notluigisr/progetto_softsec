void SFS_OptionalExpression(ScriptParser *parser)
{
	if (parser->codec->LastError) return;
	if (gf_bs_read_int(parser->bs, 1)) {
		SFS_CompoundExpression(parser);
	}
}