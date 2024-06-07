int main(int argc, char** argv) {
    U32 timestamp = FUZ_GetMilliStart();
    U32 seed=0;
    int seedset=0;
    int argNb;
    int nbTests = NB_ATTEMPTS;
    int testNb = 0;
    int proba = FUZ_COMPRESSIBILITY_DEFAULT;

    
    programName = argv[0];
    for(argNb=1; argNb<argc; argNb++)
    {
        char* argument = argv[argNb];

        if(!argument) continue;   

        
        if (argument[0]=='-')
        {
            if (!strcmp(argument, "STR")) { no_prompt=1; seedset=1; displayLevel=1; continue; }

            while (argument[1]!=0)
            {
                argument++;
                switch(*argument)
                {
                case 'h':
                    return FUZ_usage();
                case 'v':
                    argument++;
                    displayLevel=4;
                    break;
                case 'i':
                    argument++;
                    nbTests=0;
                    while ((*argument>='0') && (*argument<='9'))
                    {
                        nbTests *= 10;
                        nbTests += *argument - '0';
                        argument++;
                    }
                    break;
                case 's':
                    argument++;
                    seed=0; seedset=1;
                    while ((*argument>='0') && (*argument<='9'))
                    {
                        seed *= 10;
                        seed += *argument - '0';
                        argument++;
                    }
                    break;
                case 't':
                    argument++;
                    testNb=0;
                    while ((*argument>='0') && (*argument<='9'))
                    {
                        testNb *= 10;
                        testNb += *argument - '0';
                        argument++;
                    }
                    break;
                case 'p':
                    argument++;
                    proba=0;
                    while ((*argument>='0') && (*argument<='9'))
                    {
                        proba *= 10;
                        proba += *argument - '0';
                        argument++;
                    }
                    if (proba<0) proba=0;
                    if (proba>100) proba=100;
                    break;
                default: ;
                }
            }

        }
    }

    
    printf("STR", (int)(sizeof(size_t)*8), LZ4_VERSION);

    if (!seedset)
    {
        char userInput[50] = {0};
        printf("STR");
        fflush(stdout);
        if ( no_prompt || fgets(userInput, sizeof userInput, stdin) )
        {
            if ( sscanf(userInput, "STR", &seed) == 1 ) {}
            else seed = FUZ_GetMilliSpan(timestamp);
        }
    }
    printf("STR", seed);
    if (proba!=FUZ_COMPRESSIBILITY_DEFAULT) printf("STR", proba);

    FUZ_SecurityTest();

    if (nbTests<=0) nbTests=1;

    return FUZ_test(seed, nbTests, testNb, ((double)proba) / 100);
}