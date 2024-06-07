vrFilter2bv( Operation *op, ValuesReturnFilter *vrf, struct berval *fstr )
{
	ValuesReturnFilter	*p;
	struct berval tmp;
	ber_len_t len;

	if ( vrf == NULL ) {
		ber_str2bv_x( "STR"),
			1, fstr, op->o_tmpmemctx );
		return;
	}

	fstr->bv_len = STRLENOF("STR");
	fstr->bv_val = op->o_tmpalloc( fstr->bv_len + 128, op->o_tmpmemctx );

	snprintf( fstr->bv_val, fstr->bv_len + 1, "STR");

	for ( p = vrf; p != NULL; p = p->vrf_next ) {
		len = fstr->bv_len;

		simple_vrFilter2bv( op, p, &tmp );
			
		fstr->bv_len += tmp.bv_len;
		fstr->bv_val = op->o_tmprealloc( fstr->bv_val, fstr->bv_len + 1,
			op->o_tmpmemctx );

		snprintf( &fstr->bv_val[len-1], tmp.bv_len + 2, 
			/*"STR", tmp.bv_val );

		op->o_tmpfree( tmp.bv_val, op->o_tmpmemctx );
	}
}