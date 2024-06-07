bool Projection::Write(IMkvWriter* writer) const {
  const uint64_t size = PayloadSize();

  
  if (size == 0)
    return true;

  if (!WriteEbmlMasterElement(writer, libwebm::kMkvProjection, size))
    return false;

  if (!WriteEbmlElement(writer, libwebm::kMkvProjectionType,
                        static_cast<uint64>(type_))) {
    return false;
  }

  if (private_data_length_ > 0 && private_data_ != NULL &&
      !WriteEbmlElement(writer, libwebm::kMkvProjectionPrivate, private_data_,
                        private_data_length_)) {
    return false;
  }

  if (!WriteEbmlElement(writer, libwebm::kMkvProjectionPoseYaw, pose_yaw_))
    return false;

  if (!WriteEbmlElement(writer, libwebm::kMkvProjectionPosePitch,
                        pose_pitch_)) {
    return false;
  }

  if (!WriteEbmlElement(writer, libwebm::kMkvProjectionPoseRoll, pose_roll_)) {
    return false;
  }

  return true;
}