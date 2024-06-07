void fx_ArrayBuffer(txMachine* the)
{
	txSlot* instance;
	txInteger byteLength;
	txInteger maxByteLength = -1;
	txSlot* property;
	if (mxIsUndefined(mxTarget))
		mxTypeError("STR");
	mxPushSlot(mxTarget);
	fxGetPrototypeFromConstructor(the, &mxArrayBufferPrototype);
	instance = fxNewArrayBufferInstance(the);
	mxPullSlot(mxResult);
	byteLength = fxArgToByteLength(the, 0, 0);
	if ((mxArgc > 1) && mxIsReference(mxArgv(1))) {
		mxPushSlot(mxArgv(1));
		mxGetID(mxID(_maxByteLength));
		mxPullSlot(mxArgv(1));
		maxByteLength = fxArgToByteLength(the, 1, -1);
	}
	if (maxByteLength >= 0) {
		if (byteLength > maxByteLength)
			mxRangeError("STR");
	}
	property = instance->next;
	property->value.arrayBuffer.address = fxNewChunk(the, byteLength);
	c_memset(property->value.arrayBuffer.address, 0, byteLength);
	property = property->next;
	property->value.bufferInfo.length = byteLength;
	property->value.bufferInfo.maxLength = maxByteLength;
}