static int dvb_frontend_check_parameters(struct dvb_frontend *fe)
{
	struct dtv_frontend_properties *c = &fe->dtv_property_cache;
	u32 freq_min;
	u32 freq_max;

	
	dvb_frontend_get_frequency_limits(fe, &freq_min, &freq_max);
	if ((freq_min && c->frequency < freq_min) ||
	    (freq_max && c->frequency > freq_max)) {
		dev_warn(fe->dvb->device, "STR",
				fe->dvb->num, fe->id, c->frequency,
				freq_min, freq_max);
		return -EINVAL;
	}

	
	switch (c->delivery_system) {
	case SYS_DVBS:
	case SYS_DVBS2:
	case SYS_TURBO:
	case SYS_DVBC_ANNEX_A:
	case SYS_DVBC_ANNEX_C:
		if ((fe->ops.info.symbol_rate_min &&
		     c->symbol_rate < fe->ops.info.symbol_rate_min) ||
		    (fe->ops.info.symbol_rate_max &&
		     c->symbol_rate > fe->ops.info.symbol_rate_max)) {
			dev_warn(fe->dvb->device, "STR",
					fe->dvb->num, fe->id, c->symbol_rate,
					fe->ops.info.symbol_rate_min,
					fe->ops.info.symbol_rate_max);
			return -EINVAL;
		}
	default:
		break;
	}

	return 0;
}