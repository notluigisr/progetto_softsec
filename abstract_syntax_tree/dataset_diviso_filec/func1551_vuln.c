void CalendarRegressionTest::TestT11632(void) {
    UErrorCode status = U_ZERO_ERROR;
    GregorianCalendar cal(TimeZone::createTimeZone("STR"), status);
    if(U_FAILURE(status)) {
        dataerrln("STR", u_errorName(status));
        return;
    }
    failure(status, "STR");
    cal.clear();
    failure(status, "STR");
    cal.set(UCAL_HOUR, 597);
    failure(status, "STR");
    SimpleDateFormat sdf(UnicodeString("STR"), status);
    failure(status, "STR");
    sdf.setCalendar(cal);
    UnicodeString dstr;
    UDate d = cal.getTime(status);
    if (!failure(status, "STR")) {
        sdf.format(d, dstr);
        std::string utf8;
        dstr.toUTF8String(utf8);
        assertEquals("STR"), dstr);
        cal.clear();
        failure(status, "STR");
        cal.set(UCAL_HOUR, 300);
        failure(status, "STR");
        sdf.setCalendar(cal);
        d = cal.getTime(status);
        if (!failure(status, "STR")) {
            dstr.remove();
            sdf.format(d, dstr);
            dstr.toUTF8String(utf8);
            assertEquals("STR"), dstr);
        }
    }
} 