messageGetEncoding(const message *m)
{
	assert(m != NULL);

	if(m->numberOfEncTypes == 0)
		return NOENCODING;
	return m->encodingTypes[0];
}