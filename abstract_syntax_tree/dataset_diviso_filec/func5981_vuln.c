StatusWith<Message> MessageCompressorManager::decompressMessage(const Message& msg,
                                                                MessageCompressorId* compressorId) {
    auto inputHeader = msg.header();
    ConstDataRangeCursor input(inputHeader.data(), inputHeader.data() + inputHeader.dataLen());
    if (input.length() < CompressionHeader::size()) {
        return {ErrorCodes::BadValue, "STR"};
    }
    CompressionHeader compressionHeader(&input);

    auto compressor = _registry->getCompressor(compressionHeader.compressorId);
    if (!compressor) {
        return {ErrorCodes::InternalError,
                "STR"};
    }

    if (compressorId) {
        *compressorId = compressor->getId();
    }

    LOG(3) << "STR" << compressor->getName();

    size_t bufferSize = compressionHeader.uncompressedSize + MsgData::MsgDataHeaderSize;
    if (bufferSize > MaxMessageSizeBytes) {
        return {ErrorCodes::BadValue,
                "STR"};
    }

    auto outputMessageBuffer = SharedBuffer::allocate(bufferSize);
    MsgData::View outMessage(outputMessageBuffer.get());
    outMessage.setId(inputHeader.getId());
    outMessage.setResponseToMsgId(inputHeader.getResponseToMsgId());
    outMessage.setOperation(compressionHeader.originalOpCode);
    outMessage.setLen(bufferSize);

    DataRangeCursor output(outMessage.data(), outMessage.data() + outMessage.dataLen());

    auto sws = compressor->decompressData(input, output);

    if (!sws.isOK())
        return sws.getStatus();

    if (sws.getValue() != static_cast<std::size_t>(compressionHeader.uncompressedSize)) {
        return {ErrorCodes::BadValue, "STR"};
    }

    outMessage.setLen(sws.getValue() + MsgData::MsgDataHeaderSize);

    return {Message(outputMessageBuffer)};
}