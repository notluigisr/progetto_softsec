QPDFWriter::setLinearization(bool val)
{
    this->m->linearized = val;
    if (val)
    {
        this->m->pclm = false;
    }
}