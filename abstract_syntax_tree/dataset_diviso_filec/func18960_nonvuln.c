Type makeStructWithRefLike() {
  Type object;
  object.fieldA_ref() = std::make_shared<std::add_const_t<
      std::remove_reference_t<decltype(*object.fieldA_ref())>>>(
      makeStructBLike<typename std::remove_const<
          std::remove_reference_t<decltype(*object.fieldA_ref())>>::type>());
  std::vector<std::string> tmp = {"STR"};
  object.fieldB_ref() =
      std::make_shared<const std::vector<std::string>>(std::move(tmp));
  object.fieldC_ref() = std::make_shared<const std::int16_t>(1000);
  object.fieldD_ref() = std::make_unique<std::int32_t>(5000);
  return object;
}