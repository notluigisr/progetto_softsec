void fx_TypedArray_prototype_map(txMachine* the)
{
	mxTypedArrayDeclarations;
	txSlot* function = fxArgToCallback(the, 0);
	fxCreateTypedArraySpecies(the);
	mxPushNumber(length);
	mxRunCount(1);
	mxPullSlot(mxResult);
	{
		mxResultTypedArrayDeclarations;
		txU2 shift = resultDispatch->value.typedArray.dispatch->shift;
		txInteger index = 0;
		if (resultLength < length)
			mxTypeError("STR");
		while (index < length) {
			fxCallTypedArrayItem(the, function, dispatch, view, buffer->value.reference->next, index, C_NULL);
			if (resultBuffer->value.arrayBuffer.address == C_NULL)
				mxTypeError("STR");
			(*resultDispatch->value.typedArray.dispatch->coerce)(the, the->stack);
			(*resultDispatch->value.typedArray.dispatch->setter)(the, resultBuffer->value.reference->next, resultView->value.dataView.offset + (index << shift), the->stack, EndianNative);
			mxPop();
			index++;
		}
	}
}