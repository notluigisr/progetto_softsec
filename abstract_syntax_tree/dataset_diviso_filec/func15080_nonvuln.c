int RGWDeleteBucketWebsite::verify_permission()
{
  return verify_bucket_owner_or_policy(s, rgw::IAM::s3DeleteBucketWebsite);
}