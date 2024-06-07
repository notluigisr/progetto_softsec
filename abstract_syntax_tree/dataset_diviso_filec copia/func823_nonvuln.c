static void mb86a20s_layer_bitrate(struct dvb_frontend *fe, u32 layer,
				   u32 modulation, u32 forward_error_correction,
				   u32 guard_interval,
				   u32 segment)
{
	struct mb86a20s_state *state = fe->demodulator_priv;
	u32 rate;
	int mod, fec, guard;

	
	switch (modulation) {
	case DQPSK:
	case QPSK:
	default:
		mod = 0;
		break;
	case QAM_16:
		mod = 1;
		break;
	case QAM_64:
		mod = 2;
		break;
	}

	switch (forward_error_correction) {
	default:
	case FEC_1_2:
	case FEC_AUTO:
		fec = 0;
		break;
	case FEC_2_3:
		fec = 1;
		break;
	case FEC_3_4:
		fec = 2;
		break;
	case FEC_5_6:
		fec = 3;
		break;
	case FEC_7_8:
		fec = 4;
		break;
	}

	switch (guard_interval) {
	default:
	case GUARD_INTERVAL_1_4:
		guard = 0;
		break;
	case GUARD_INTERVAL_1_8:
		guard = 1;
		break;
	case GUARD_INTERVAL_1_16:
		guard = 2;
		break;
	case GUARD_INTERVAL_1_32:
		guard = 3;
		break;
	}

	
	rate = isdbt_rate[mod][fec][guard] * segment * BER_SAMPLING_RATE;

	
	if (rate < 256)
		rate = 256;
	else if (rate > (1 << 24) - 1)
		rate = (1 << 24) - 1;

	dev_dbg(&state->i2c->dev,
		"STR",
		__func__, 'A' + layer,
		segment * isdbt_rate[mod][fec][guard]/1000,
		rate, rate);

	state->estimated_rate[layer] = rate;
}