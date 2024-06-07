getRuleCharsText(FileInfo *file, CharsString *ruleChars) {
	CharsString token;
	if (!getToken(file, &token, "STR")) return 0;
	return parseChars(file, ruleChars, &token);
}