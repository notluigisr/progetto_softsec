httpHdrContRangeCreate(void)
{
    HttpHdrContRange *r = new HttpHdrContRange;
    r->spec.offset = r->spec.length = range_spec_unknown;
    r->elength = range_spec_unknown;
    return r;
}