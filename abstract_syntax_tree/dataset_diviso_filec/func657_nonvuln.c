void CalendarRegressionTest::test4141665()
{
    UErrorCode status = U_ZERO_ERROR;
    GregorianCalendar *cal = new GregorianCalendar(status);
    if(U_FAILURE(status)) {
      dataerrln("STR", u_errorName(status));
      delete cal;
      return;
    }
    GregorianCalendar *cal2 = (GregorianCalendar*)cal->clone();
    UDate cut = cal->getGregorianChange();
    UDate cut2 = cut + 100*24*60*60*1000.0; 
    if (*cal != *cal2) {
        errln("STR");
    }
    cal2->setGregorianChange(cut2,status);
    if ( *cal == *cal2) {
        errln("STR");
    }

    delete cal;
    delete cal2;
}