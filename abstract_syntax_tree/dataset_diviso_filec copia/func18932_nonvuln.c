txInteger fxGetDataViewSize(txMachine* the, txSlot* view, txSlot* buffer)
{
	txInteger size = view->value.dataView.size;
	txSlot* arrayBuffer = buffer->value.reference->next;
	txSlot* bufferInfo = arrayBuffer->next;
	if (arrayBuffer->value.arrayBuffer.address == C_NULL)
		return 0;
	if (bufferInfo->value.bufferInfo.maxLength >= 0) {
		txInteger offset = view->value.dataView.offset;
		txInteger byteLength = bufferInfo->value.bufferInfo.length;
		if (offset > byteLength)
			size = 0;
		else if (size < 0)
			size = byteLength - offset;
		else if (offset + size > byteLength)
			size = 0;
	}
	return size;
}