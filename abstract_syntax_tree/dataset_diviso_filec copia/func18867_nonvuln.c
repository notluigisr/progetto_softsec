compound_rrstream_first(rrstream_t *rs) {
	compound_rrstream_t *s = (compound_rrstream_t *) rs;
	s->state = 0;
	do {
		rrstream_t *curstream = s->components[s->state];
		s->result = curstream->methods->first(curstream);
	} while (s->result == ISC_R_NOMORE && s->state < 2);
	return (s->result);
}