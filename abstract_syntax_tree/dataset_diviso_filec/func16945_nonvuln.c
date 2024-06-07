bool SSL_CTX::SetDH(const DH& dh)
{
    dhParms_.p_ = dh.p->int_;
    dhParms_.g_ = dh.g->int_;

    return dhParms_.set_ = true;
}