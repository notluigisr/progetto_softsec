unsigned long long qpdf_get_error_file_position(qpdf_data qpdf, qpdf_error e)
{
    if (e == 0)
    {
	return 0;
    }
    return e->exc->getFilePosition();
}