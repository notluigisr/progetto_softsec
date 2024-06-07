DatumGetFloat4(Datum X)
{
	union
	{
		int32		value;
		float4		retval;
	}			myunion;

	myunion.value = GET_4_BYTES(X);
	return myunion.retval;
}