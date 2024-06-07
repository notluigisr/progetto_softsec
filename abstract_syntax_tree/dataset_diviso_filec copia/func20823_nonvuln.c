static int skiploop(void)
{
	int skip = evalskip;

	switch (skip) {
	case 0:
		break;

	case SKIPBREAK:
	case SKIPCONT:
		if (likely(--skipcount <= 0)) {
			evalskip = 0;
			break;
		}

		skip = SKIPBREAK;
		break;
	}

	return skip;
}