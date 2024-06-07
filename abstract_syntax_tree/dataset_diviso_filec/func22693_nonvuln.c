void fx_TypedArray_prototype_filter(txMachine* the)
{
	mxTypedArrayDeclarations;
	txSlot* function = fxArgToCallback(the, 0);
	txSlot* list = fxNewInstance(the);
	txSlot* slot = list;
	txInteger count = 0;
	txInteger index = 0;
	mxPushUndefined();
	while (index < length) {
		fxCallTypedArrayItem(the, function, dispatch, view, buffer->value.reference->next, index, the->stack);
		if (fxToBoolean(the, the->stack++)) {
			count++;
			slot = fxNextSlotProperty(the, slot, the->stack, XS_NO_ID, XS_NO_FLAG);
		}
		index++;
	}
	mxPop();
	fxCreateTypedArraySpecies(the);
	mxPushNumber(count);
	mxRunCount(1);
	mxPullSlot(mxResult);
	{
		mxResultTypedArrayDeclarations;
		txInteger resultOffset = 0;
		txInteger resultSize = resultDispatch->value.typedArray.dispatch->size;
		if (resultLength < count)
			mxTypeError("STR");
		slot = list->next;
		while (slot) {
			(*resultDispatch->value.typedArray.dispatch->coerce)(the, slot);
			(*resultDispatch->value.typedArray.dispatch->setter)(the, resultBuffer->value.reference->next, resultOffset, slot, EndianNative);
			resultOffset += resultSize;
			slot = slot->next;
		}
	}
	mxPop();
}