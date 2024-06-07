Header::setChunkCount(int chunks)
{
    insert("STR",IntAttribute(chunks));
}