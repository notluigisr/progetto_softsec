static u32 *gen9_init_indirectctx_bb(struct intel_engine_cs *engine, u32 *batch)
{
	static const struct lri lri[] = {
		
		{
			COMMON_SLICE_CHICKEN2,
			__MASKED_FIELD(GEN9_DISABLE_GATHER_AT_SET_SHADER_COMMON_SLICE,
				       0),
		},

		
		{
			FF_SLICE_CHICKEN,
			__MASKED_FIELD(FF_SLICE_CHICKEN_CL_PROVOKING_VERTEX_FIX,
				       FF_SLICE_CHICKEN_CL_PROVOKING_VERTEX_FIX),
		},

		
		{
			_3D_CHICKEN3,
			__MASKED_FIELD(_3D_CHICKEN_SF_PROVOKING_VERTEX_FIX,
				       _3D_CHICKEN_SF_PROVOKING_VERTEX_FIX),
		}
	};

	*batch++ = MI_ARB_ON_OFF | MI_ARB_DISABLE;

	
	batch = gen8_emit_flush_coherentl3_wa(engine, batch);

	batch = emit_lri(batch, lri, ARRAY_SIZE(lri));

	
	if (HAS_POOLED_EU(engine->i915)) {
		
		*batch++ = GEN9_MEDIA_POOL_STATE;
		*batch++ = GEN9_MEDIA_POOL_ENABLE;
		*batch++ = 0x00777000;
		*batch++ = 0;
		*batch++ = 0;
		*batch++ = 0;
	}

	*batch++ = MI_ARB_ON_OFF | MI_ARB_ENABLE;

	
	while ((unsigned long)batch % CACHELINE_BYTES)
		*batch++ = MI_NOOP;

	return batch;
}