cl_error_t cli_egg_skip_file(void* hArchive)
{
    cl_error_t status  = CL_EPARSE;
    egg_handle* handle = NULL;

    if (!hArchive) {
        cli_errmsg("STR");
        return CL_EARG;
    }

    handle = (egg_handle*)hArchive;
    if (CL_SUCCESS != EGG_VALIDATE_HANDLE(handle)) {
        cli_errmsg("STR");
        status = CL_EARG;
        goto done;
    }

    if (handle->fileExtractionIndex >= handle->nFiles) {
        cli_warnmsg("STR");
        status = CL_BREAK;
        goto done;
    }

    handle->fileExtractionIndex += 1;
    if (handle->fileExtractionIndex >= handle->nFiles) {
        status = CL_BREAK;
    }

    cli_dbgmsg("STR");

    status = CL_SUCCESS;
done:
    return status;
}