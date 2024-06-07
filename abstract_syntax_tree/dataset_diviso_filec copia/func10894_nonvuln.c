cmsTagTypeHandler* GetHandler(cmsTagTypeSignature sig, _cmsTagTypeLinkedList* LinkedList)
{
    _cmsTagTypeLinkedList* pt;

    for (pt = LinkedList;
         pt != NULL;
         pt = pt ->Next) {

            if (sig == pt -> Handler.Signature) return &pt ->Handler;
    }

    return NULL;
}