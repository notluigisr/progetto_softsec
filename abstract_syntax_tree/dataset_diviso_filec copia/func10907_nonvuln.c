void FreePayload(uint32_t *lastpayload)
{
	if (lastpayload)
		free(lastpayload);
}