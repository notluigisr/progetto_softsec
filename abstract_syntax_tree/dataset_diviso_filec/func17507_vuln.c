TRIO_PRIVATE void TrioWriteString TRIO_ARGS5((self, string, flags, width, precision),
                                             trio_class_t* self, TRIO_CONST char* string,
                                             trio_flags_t flags, int width, int precision)
{
	int length;
	int ch;

	assert(VALID(self));
	assert(VALID(self->OutStream));

	if (string == NULL)
	{
		string = internalNullString;
		length = sizeof(internalNullString) - 1;
#if TRIO_FEATURE_QUOTE
		
		flags &= (~FLAGS_QUOTE);
#endif
		width = 0;
	}
	else
	{
		if (precision == 0)
		{
			length = trio_length(string);
		}
		else
		{
			length = trio_length_max(string, precision);
		}
	}
	if ((NO_PRECISION != precision) && (precision < length))
	{
		length = precision;
	}
	width -= length;

#if TRIO_FEATURE_QUOTE
	if (flags & FLAGS_QUOTE)
		self->OutStream(self, CHAR_QUOTE);
#endif

	if (!(flags & FLAGS_LEFTADJUST))
	{
		while (width-- > 0)
			self->OutStream(self, CHAR_ADJUST);
	}

	while (length-- > 0)
	{
		
		ch = (int)((unsigned char)(*string++));
		TrioWriteStringCharacter(self, ch, flags);
	}

	if (flags & FLAGS_LEFTADJUST)
	{
		while (width-- > 0)
			self->OutStream(self, CHAR_ADJUST);
	}
#if TRIO_FEATURE_QUOTE
	if (flags & FLAGS_QUOTE)
		self->OutStream(self, CHAR_QUOTE);
#endif
}