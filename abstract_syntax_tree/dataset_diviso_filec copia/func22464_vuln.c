rdpBitmap* bitmap_cache_get(rdpBitmapCache* bitmapCache, UINT32 id, UINT32 index)
{
	rdpBitmap* bitmap;

	if (id > bitmapCache->maxCells)
	{
		WLog_ERR(TAG, "STR", id);
		return NULL;
	}

	if (index == BITMAP_CACHE_WAITING_LIST_INDEX)
	{
		index = bitmapCache->cells[id].number;
	}
	else if (index > bitmapCache->cells[id].number)
	{
		WLog_ERR(TAG, "STR", index, id);
		return NULL;
	}

	bitmap = bitmapCache->cells[id].entries[index];
	return bitmap;
}