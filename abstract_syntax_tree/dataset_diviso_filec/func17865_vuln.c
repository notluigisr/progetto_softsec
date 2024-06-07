void _modinit(module_t *m)
{
	service_named_bind_command("STR", &cs_flags);
}