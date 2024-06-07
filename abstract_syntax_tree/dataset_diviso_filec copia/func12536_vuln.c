BOOL update_write_cache_brush_order(wStream* s, const CACHE_BRUSH_ORDER* cache_brush, UINT16* flags)
{
	int i;
	BYTE iBitmapFormat;
	BOOL compressed = FALSE;

	if (!Stream_EnsureRemainingCapacity(s,
	                                    update_approximate_cache_brush_order(cache_brush, flags)))
		return FALSE;

	iBitmapFormat = BPP_BMF[cache_brush->bpp];
	Stream_Write_UINT8(s, cache_brush->index);  
	Stream_Write_UINT8(s, iBitmapFormat);       
	Stream_Write_UINT8(s, cache_brush->cx);     
	Stream_Write_UINT8(s, cache_brush->cy);     
	Stream_Write_UINT8(s, cache_brush->style);  
	Stream_Write_UINT8(s, cache_brush->length); 

	if ((cache_brush->cx == 8) && (cache_brush->cy == 8))
	{
		if (cache_brush->bpp == 1)
		{
			if (cache_brush->length != 8)
			{
				WLog_ERR(TAG, "STR", cache_brush->length);
				return FALSE;
			}

			for (i = 7; i >= 0; i--)
			{
				Stream_Write_UINT8(s, cache_brush->data[i]);
			}
		}
		else
		{
			if ((iBitmapFormat == BMF_8BPP) && (cache_brush->length == 20))
				compressed = TRUE;
			else if ((iBitmapFormat == BMF_16BPP) && (cache_brush->length == 24))
				compressed = TRUE;
			else if ((iBitmapFormat == BMF_32BPP) && (cache_brush->length == 32))
				compressed = TRUE;

			if (compressed != FALSE)
			{
				
				if (!update_compress_brush(s, cache_brush->data, cache_brush->bpp))
					return FALSE;
			}
			else
			{
				
				int scanline = (cache_brush->bpp / 8) * 8;

				for (i = 7; i >= 0; i--)
				{
					Stream_Write(s, &cache_brush->data[i * scanline], scanline);
				}
			}
		}
	}

	return TRUE;
}