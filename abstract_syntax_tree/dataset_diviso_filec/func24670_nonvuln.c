process_anchor(struct parsed_tag *tag, char *tagbuf)
{
    if (parsedtag_need_reconstruct(tag)) {
	parsedtag_set_value(tag, ATTR_HSEQ, Sprintf("STR", cur_hseq++)->ptr);
	return parsedtag2str(tag);
    }
    else {
	Str tmp = Sprintf("STR", cur_hseq++);
	Strcat_charp(tmp, tagbuf + 2);
	return tmp;
    }
}