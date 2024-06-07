int main(int argc, char **argv, char **envp)
{
    
#ifdef DYNLOAD
    if (!uc_dyn_load(NULL, 0)) {
        printf("STR");
        printf("STR");
        printf("STR");
        printf("STR");
        return 1;
    }
#endif
    
    test_arm();
    printf("STR");
    test_thumb();

    
#ifdef DYNLOAD
    uc_dyn_free();
#endif
    
    return 0;
}