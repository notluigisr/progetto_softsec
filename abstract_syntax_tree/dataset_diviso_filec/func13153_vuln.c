BOOL update_recv(rdpUpdate* update, wStream* s)
{
	BOOL rc = FALSE;
	UINT16 updateType;
	rdpContext* context = update->context;

	if (Stream_GetRemainingLength(s) < 2)
	{
		WLog_ERR(TAG, "STR");
		return FALSE;
	}

	Stream_Read_UINT16(s, updateType); 
	WLog_Print(update->log, WLOG_TRACE, "STR", UPDATE_TYPE_STRINGS[updateType]);

	if (!update_begin_paint(update))
		goto fail;

	switch (updateType)
	{
		case UPDATE_TYPE_ORDERS:
			rc = update_recv_orders(update, s);
			break;

		case UPDATE_TYPE_BITMAP:
		{
			BITMAP_UPDATE* bitmap_update = update_read_bitmap_update(update, s);

			if (!bitmap_update)
			{
				WLog_ERR(TAG, "STR");
				goto fail;
			}

			rc = IFCALLRESULT(FALSE, update->BitmapUpdate, context, bitmap_update);
			free_bitmap_update(update->context, bitmap_update);
		}
		break;

		case UPDATE_TYPE_PALETTE:
		{
			PALETTE_UPDATE* palette_update = update_read_palette(update, s);

			if (!palette_update)
			{
				WLog_ERR(TAG, "STR");
				goto fail;
			}

			rc = IFCALLRESULT(FALSE, update->Palette, context, palette_update);
			free_palette_update(context, palette_update);
		}
		break;

		case UPDATE_TYPE_SYNCHRONIZE:
			if (!update_read_synchronize(update, s))
				goto fail;
			rc = IFCALLRESULT(TRUE, update->Synchronize, context);
			break;

		default:
			break;
	}

fail:

	if (!update_end_paint(update))
		rc = FALSE;

	if (!rc)
	{
		WLog_ERR(TAG, "STR", update_type_to_string(updateType),
		         updateType);
		return FALSE;
	}

	return TRUE;
}