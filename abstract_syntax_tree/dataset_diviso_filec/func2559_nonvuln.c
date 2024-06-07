Formattable::setDecimalNumber(StringPiece numberString, UErrorCode &status) {
    if (U_FAILURE(status)) {
        return;
    }
    dispose();

    auto* dq = new DecimalQuantity();
    dq->setToDecNumber(numberString, status);
    adoptDecimalQuantity(dq);

    
    
}