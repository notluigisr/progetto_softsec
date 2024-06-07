JSObject *create(JSContext *cx, HandleObject response, ResponseHandle response_handle,
                 BodyHandle body_handle, bool is_upstream) {
  JS::SetReservedSlot(response, Slots::Response, JS::Int32Value(response_handle.handle));
  JS::SetReservedSlot(response, Slots::Headers, JS::NullValue());
  JS::SetReservedSlot(response, Slots::Body, JS::Int32Value(body_handle.handle));
  JS::SetReservedSlot(response, Slots::BodyStream, JS::NullValue());
  JS::SetReservedSlot(response, Slots::HasBody, JS::FalseValue());
  JS::SetReservedSlot(response, Slots::BodyUsed, JS::FalseValue());
  JS::SetReservedSlot(response, Slots::IsUpstream, JS::BooleanValue(is_upstream));

  if (is_upstream) {
    uint16_t status = 0;
    if (!HANDLE_RESULT(cx, xqd_resp_status_get(response_handle, &status)))
      return nullptr;

    JS::SetReservedSlot(response, Slots::Status, JS::Int32Value(status));
    set_status_message_from_code(cx, response, status);

    if (!(status == 204 || status == 205 || status == 304)) {
      JS::SetReservedSlot(response, Slots::HasBody, JS::TrueValue());
    }
  }

  return response;
}