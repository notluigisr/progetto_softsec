txBoolean fxTypedArrayHasProperty(txMachine* the, txSlot* instance, txID id, txIndex index)
{
	if ((!id) || fxIsCanonicalIndex(the, id)) {
		txSlot* dispatch = instance->next;
		txSlot* view = dispatch->next;
		txSlot* buffer = view->next;
		txU2 shift = dispatch->value.typedArray.dispatch->shift;
		txIndex length = fxGetDataViewSize(the, view, buffer) >> shift;
		return ((!id) && (index < length)) ? 1 : 0;
	}
	return fxOrdinaryHasProperty(the, instance, id, index);
}