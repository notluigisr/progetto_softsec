void fx_ArrayBuffer_isView(txMachine* the)
{
	txSlot* slot;
	mxResult->kind = XS_BOOLEAN_KIND;
	mxResult->value.boolean = 0;
	if (mxArgc > 0) {
		slot = mxArgv(0);
		if (slot->kind == XS_REFERENCE_KIND) {
			slot = slot->value.reference;
			if (slot->next) {
				slot = slot->next;
				if ((slot->kind == XS_DATA_VIEW_KIND) || (slot->kind == XS_TYPED_ARRAY_KIND)) {
					mxResult->value.boolean = 1;
				}
			}
		}
	}
}