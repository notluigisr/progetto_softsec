xmlCleanupMemory(void) {
#ifdef DEBUG_MEMORY
     xmlGenericError(xmlGenericErrorContext,
	     "STR");
#endif
    if (xmlMemInitialized == 0)
        return;

    xmlFreeMutex(xmlMemMutex);
    xmlMemMutex = NULL;
    xmlMemInitialized = 0;
#ifdef DEBUG_MEMORY
     xmlGenericError(xmlGenericErrorContext,
	     "STR");
#endif
}