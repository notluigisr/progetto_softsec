txInteger fxGetArrayBufferMaxLength(txMachine* the, txSlot* slot)
{
	txSlot* instance = fxCheckArrayBufferInstance(the, slot);
	txSlot* arrayBuffer = instance->next;
	txSlot* bufferInfo = arrayBuffer->next;
	return bufferInfo->value.bufferInfo.maxLength;
}