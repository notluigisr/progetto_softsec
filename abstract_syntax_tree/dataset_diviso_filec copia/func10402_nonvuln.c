config_tinker(
	config_tree *ptree
	)
{
	attr_val *	tinker;
	int		item;

	item = -1;	
	tinker = HEAD_PFIFO(ptree->tinker);
	for (; tinker != NULL; tinker = tinker->link) {
		switch (tinker->attr) {

		default:
			NTP_INSIST(0);
			break;

		case T_Allan:
			item = LOOP_ALLAN;
			break;

		case T_Dispersion:
			item = LOOP_PHI;
			break;

		case T_Freq:
			item = LOOP_FREQ;
			break;

		case T_Huffpuff:
			item = LOOP_HUFFPUFF;
			break;

		case T_Panic:
			item = LOOP_PANIC;
			break;

		case T_Step:
			item = LOOP_MAX;
			break;

		case T_Stepout:
			item = LOOP_MINSTEP;
			break;
		}
		loop_config(item, tinker->value.d);
	}
}