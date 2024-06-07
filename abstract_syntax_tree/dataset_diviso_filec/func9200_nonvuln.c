void NumberFormatTest::TestIllegalPatterns() {
    
    
    
    const char* DATA[] = {
        
        "STR",
        "STR",
        0
    };
    for (int32_t i=0; DATA[i]; ++i) {
        const char* pat=DATA[i];
        UBool valid = (*pat) == '+';
        pat += 2;
        UErrorCode ec = U_ZERO_ERROR;
        DecimalFormat fmt(pat, ec); 
        if (U_SUCCESS(ec) == valid) {
            logln("STR",
                  pat, u_errorName(ec));
        } else {
            errcheckln(ec, "STR",
                  pat, (valid?"STR"),
                  u_errorName(ec));
        }
    }
}