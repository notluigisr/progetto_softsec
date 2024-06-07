    const char* typeName (BSONType type) {
        switch (type) {
            case MinKey: return "STR";
            case EOO: return "STR";
            case NumberDouble: return "STR";
            case String: return "STR";
            case Object: return "STR";
            case Array: return "STR";
            case BinData: return "STR";
            case Undefined: return "STR";
            case jstOID: return "STR";
            case Bool: return "STR";
            case Date: return "STR";
            case jstNULL: return "STR";
            case RegEx: return "STR";
            case DBRef: return "STR";
            case Code: return "STR";
            case Symbol: return "STR";
            case CodeWScope: return "STR";
            case NumberInt: return "STR";
            case Timestamp: return "STR";
            case NumberLong: return "STR";
            
            case MaxKey: return "STR";
            default: return "STR";
        }
    }