StatusWith<Message> MessageCompressorManager::decompressMessage(const Message& msg) {
    auto inputHeader = msg.header();
    ConstDataRangeCursor input(inputHeader.data(), inputHeader.data() + inputHeader.dataLen());
    CompressionHeader compressionHeader(&input);

    auto compressor = _registry->getCompressor(compressionHeader.compressorId);
    if (!compressor) {
        return {ErrorCodes::InternalError,
                "STR"};
    }

    auto bufferSize = compressionHeader.uncompressedSize + MsgData::MsgDataHeaderSize;
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