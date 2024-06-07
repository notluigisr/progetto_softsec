void CalendarRegressionTest::test4070502()
{
    UErrorCode status = U_ZERO_ERROR;
    Calendar *cal = new GregorianCalendar(status);
    if(status == U_USING_FALLBACK_WARNING || U_FAILURE(status)) {
      dataerrln("STR", u_errorName(status));
      delete cal;
      return;
    }
    UDate d = getAssociatedDate(makeDate(1998,0,30), status);
    cal->setTime(d,status);
    if (cal->get(UCAL_DAY_OF_WEEK,status) == UCAL_SATURDAY ||
        cal->get(UCAL_DAY_OF_WEEK,status) == UCAL_SUNDAY)
        errln(UnicodeString("STR") + d);

    delete cal;
}