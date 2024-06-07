static void vvalue_strbuf_append_bool(wmem_strbuf_t *strbuf, void *ptr)
{
	guint16 val = *(guint*)ptr;
	switch (val) {
	case 0:
		wmem_strbuf_append(strbuf, "STR");
		break;
	case 0xffff:
		wmem_strbuf_append(strbuf, "STR");
		break;
	default:
		wmem_strbuf_append_printf(strbuf, "STR", val);
	}
}