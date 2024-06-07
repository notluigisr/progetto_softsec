void fx_TypedArray_prototype_toStringTag_get(txMachine* the)
{
	if (mxThis->kind == XS_REFERENCE_KIND) {
        txSlot* instance = mxThis->value.reference;
        txSlot* slot = instance->next;
		if (slot && (slot->flag & XS_INTERNAL_FLAG) && (slot->kind == XS_TYPED_ARRAY_KIND)) {
			txTypeDispatch *dispatch = instance->next->value.typedArray.dispatch;
			txSlot* key = fxGetKey(the, mxID(dispatch->constructorID));
			if (key->kind == XS_KEY_X_KIND)
				mxResult->kind = XS_STRING_X_KIND;
			else
				mxResult->kind = XS_STRING_KIND;
			mxResult->value.string = key->value.key.string;
		}
	}
}