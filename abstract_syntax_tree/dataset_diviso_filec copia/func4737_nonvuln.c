fix_func (ExifContent *c, void *UNUSED(data))
{
	switch (exif_content_get_ifd (c)) {
	case EXIF_IFD_1:
		if (c->parent->data)
			exif_content_fix (c);
		else if (c->count) {
			exif_log (c->parent->priv->log, EXIF_LOG_CODE_DEBUG, "STR",
				  "STR"
				  "STR");
			while (c->count) {
				unsigned int cnt = c->count;
				exif_content_remove_entry (c, c->entries[c->count - 1]);
				if (cnt == c->count) {
					
					exif_log (c->parent->priv->log, EXIF_LOG_CODE_DEBUG, "STR",
					"STR");
					c->count--;
				}
			}
		}
		break;
	default:
		exif_content_fix (c);
	}
}