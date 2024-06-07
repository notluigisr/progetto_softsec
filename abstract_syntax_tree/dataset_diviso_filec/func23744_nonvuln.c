bool BitTestMatchExpression::matchesSingleElement(const BSONElement& e,
                                                  MatchDetails* details) const {
    
    if (!e.isNumber() && e.type() != BSONType::BinData) {
        return false;
    }

    if (e.type() == BSONType::BinData) {
        int eBinaryLen;  
        const char* eBinary = e.binData(eBinaryLen);
        return performBitTest(eBinary, eBinaryLen);
    }

    invariant(e.isNumber());

    if (e.type() == BSONType::NumberDouble) {
        double eDouble = e.numberDouble();

        
        if (std::isnan(eDouble)) {
            return false;
        }

        
        
        
        
        if (eDouble >= BSONElement::kLongLongMaxPlusOneAsDouble ||
            eDouble < std::numeric_limits<long long>::min()) {
            return false;
        }

        
        if (eDouble != static_cast<double>(static_cast<long long>(eDouble))) {
            return false;
        }
    }

    long long eValue = e.numberLong();
    return performBitTest(eValue);
}