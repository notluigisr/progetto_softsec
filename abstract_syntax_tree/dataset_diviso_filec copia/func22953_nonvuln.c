static void SerializeSpotLight(SpotLight &spot, json &o) {
  SerializeNumberProperty("STR", spot.innerConeAngle, o);
  SerializeNumberProperty("STR", spot.outerConeAngle, o);
  SerializeExtensionMap(spot.extensions, o);
  if (spot.extras.Type() != NULL_TYPE) {
    SerializeValue("STR", spot.extras, o);
  }
}