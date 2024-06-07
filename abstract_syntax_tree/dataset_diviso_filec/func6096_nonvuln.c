eval_init(void)
{
    evalvars_init();
    func_init();

#ifdef EBCDIC
    
    sortFunctions();
#endif
}