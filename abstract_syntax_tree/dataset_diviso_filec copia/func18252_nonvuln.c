  explicit StringView(UTF16Ref utf16Ref)
      : nonManagedStringPtr_(utf16Ref.data()),
        startIndex_(0),
        isHandle_(false),
        isASCII_(false),
        length_(utf16Ref.size()) {}