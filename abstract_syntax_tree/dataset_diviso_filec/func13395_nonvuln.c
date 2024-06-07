int32_t PersianCalendar::handleGetLimit(UCalendarDateFields field, ELimitType limitType) const {
    return kPersianCalendarLimits[field][limitType];
}