m_wnumx(union DateData *x, int f)
{
    int ry, rw, rd;

    c_jd_to_weeknum(m_local_jd(x), f, m_virtual_sg(x), 
		    &ry, &rw, &rd);
    return rw;
}