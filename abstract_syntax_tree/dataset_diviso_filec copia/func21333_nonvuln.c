void fxUint32Setter(txMachine* the, txSlot* data, txInteger offset, txSlot* slot, int endian)
{
	txU4 value = (slot->kind == XS_INTEGER_KIND) ? (txU4)slot->value.integer : (txU4)slot->value.number;
#ifdef mxMisalignedSettersCrash
	value = EXPORT(U32);
	c_memcpy(data->value.arrayBuffer.address + offset, &value, sizeof(txU4));
#else
	*((txU4*)(data->value.arrayBuffer.address + offset)) = EXPORT(U32);
#endif
	mxMeterOne();
}