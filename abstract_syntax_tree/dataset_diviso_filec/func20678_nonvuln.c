QPDF::checkLinearization()
{
    bool result = false;
    try
    {
	readLinearizationData();
	result = checkLinearizationInternal();
    }
    catch (QPDFExc& e)
    {
	*this->m->out_stream << e.what() << std::endl;
    }
    return result;
}