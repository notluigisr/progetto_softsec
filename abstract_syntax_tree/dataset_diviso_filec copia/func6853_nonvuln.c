void fx_TypedArray_prototype_find(txMachine* the)
{
	mxTypedArrayDeclarations;
	txSlot* function = fxArgToCallback(the, 0);
	txInteger index = 0;
	mxPushUndefined();
	while (index < length) {
		fxCallTypedArrayItem(the, function, dispatch, view, buffer->value.reference->next, index, the->stack);
		if (fxToBoolean(the, the->stack++)) {
			mxResult->kind = the->stack->kind;
			mxResult->value = the->stack->value;
			break;
		}
		index++;
	}
	mxPop();
}