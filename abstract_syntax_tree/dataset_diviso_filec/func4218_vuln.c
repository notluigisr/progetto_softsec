static INLINE BOOL update_read_delta_rects(wStream* s, DELTA_RECT* rectangles, UINT32 number)
{
	UINT32 i;
	BYTE flags = 0;
	BYTE* zeroBits;
	UINT32 zeroBitsSize;

	if (number > 45)
		number = 45;

	zeroBitsSize = ((number + 1) / 2);

	if (Stream_GetRemainingLength(s) < zeroBitsSize)
		return FALSE;

	Stream_GetPointer(s, zeroBits);
	Stream_Seek(s, zeroBitsSize);
	ZeroMemory(rectangles, sizeof(DELTA_RECT) * number);

	for (i = 0; i < number; i++)
	{
		if (i % 2 == 0)
			flags = zeroBits[i / 2];

		if ((~flags & 0x80) && !update_read_delta(s, &rectangles[i].left))
			return FALSE;

		if ((~flags & 0x40) && !update_read_delta(s, &rectangles[i].top))
			return FALSE;

		if (~flags & 0x20)
		{
			if (!update_read_delta(s, &rectangles[i].width))
				return FALSE;
		}
		else if (i > 0)
			rectangles[i].width = rectangles[i - 1].width;
		else
			rectangles[i].width = 0;

		if (~flags & 0x10)
		{
			if (!update_read_delta(s, &rectangles[i].height))
				return FALSE;
		}
		else if (i > 0)
			rectangles[i].height = rectangles[i - 1].height;
		else
			rectangles[i].height = 0;

		if (i > 0)
		{
			rectangles[i].left += rectangles[i - 1].left;
			rectangles[i].top += rectangles[i - 1].top;
		}

		flags <<= 4;
	}

	return TRUE;
}