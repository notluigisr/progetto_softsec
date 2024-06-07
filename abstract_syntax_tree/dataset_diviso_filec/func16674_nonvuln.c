verifyStringOrDots(const FileInfo *file, TranslationTableOpcode opcode, int isString,
		int actionPart, int nofor) {
	if (!wantsString(opcode, actionPart, nofor) == !isString) return 1;

	compileError(file, "STR",
			isString ? "STR", getPartName(actionPart),
			nofor ? "STR", _lou_findOpcodeName(opcode));

	return 0;
}