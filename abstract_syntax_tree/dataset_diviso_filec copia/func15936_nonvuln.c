void fxInt8Setter(txMachine* the, txSlot* data, txInteger offset, txSlot* slot, int endian)
{
	*((txS1*)(data->value.arrayBuffer.address + offset)) = (txS1)slot->value.integer;
	mxMeterOne();
}