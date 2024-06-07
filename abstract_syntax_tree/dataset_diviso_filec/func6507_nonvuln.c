cmsBool  MemoryClose(struct _cms_io_handler* iohandler)
{
    FILEMEM* ResData = (FILEMEM*) iohandler ->stream;

    if (ResData ->FreeBlockOnClose) {

        if (ResData ->Block) _cmsFree(iohandler ->ContextID, ResData ->Block);
    }

    _cmsFree(iohandler ->ContextID, ResData);
    _cmsFree(iohandler ->ContextID, iohandler);

    return TRUE;
}