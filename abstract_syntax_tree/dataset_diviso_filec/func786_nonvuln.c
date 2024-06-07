ServerDHParams::~ServerDHParams()
{
    ysArrayDelete(Ys_);
    ysArrayDelete(g_);
    ysArrayDelete(p_);
}