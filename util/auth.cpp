#include "auth.h"
#include "base64.h"

static unsigned char __gbv2keypub_der[] = {
  0x30, 0x82, 0x01, 0x22, 0x30, 0x0d, 0x06, 0x09, 0x2a, 0x86, 0x48, 0x86,
  0xf7, 0x0d, 0x01, 0x01, 0x01, 0x05, 0x00, 0x03, 0x82, 0x01, 0x0f, 0x00,
  0x30, 0x82, 0x01, 0x0a, 0x02, 0x82, 0x01, 0x01, 0x00, 0xe5, 0xd7, 0x9c,
  0x7d, 0x73, 0xc6, 0xe6, 0xfb, 0x35, 0x7e, 0xd7, 0x57, 0x99, 0x07, 0xdb,
  0x99, 0x70, 0xc9, 0xd0, 0x3e, 0x53, 0x57, 0x3c, 0x1e, 0x55, 0xda, 0x0f,
  0x69, 0xbf, 0x26, 0x79, 0xc7, 0xb6, 0xdd, 0x8e, 0x83, 0x32, 0x65, 0x74,
  0x0d, 0x74, 0x48, 0x42, 0x49, 0x22, 0x52, 0x58, 0x56, 0xc3, 0xe4, 0x49,
  0x5d, 0xac, 0x6a, 0x94, 0xb1, 0x64, 0x14, 0xbf, 0x4d, 0xd5, 0xd7, 0x3a,
  0xca, 0x5c, 0x1e, 0x6f, 0x42, 0x30, 0xac, 0x29, 0xaa, 0xa0, 0x85, 0xd2,
  0x16, 0xa2, 0x8e, 0x89, 0x12, 0xc4, 0x92, 0x06, 0xea, 0xed, 0x48, 0xf6,
  0xdb, 0xed, 0x4f, 0x62, 0x6c, 0xfa, 0xcf, 0xc2, 0xb9, 0x8d, 0x04, 0xb2,
  0xba, 0x63, 0xc9, 0xcc, 0xee, 0x23, 0x64, 0x46, 0x14, 0x12, 0xc8, 0x38,
  0x67, 0x69, 0x6b, 0xaf, 0xd1, 0x7c, 0xb1, 0xb5, 0x79, 0xe4, 0x4e, 0x3a,
  0xa7, 0xe8, 0x28, 0x89, 0x25, 0xc0, 0xd0, 0xd8, 0xc7, 0xd2, 0x26, 0xaa,
  0xf5, 0xbf, 0x36, 0x55, 0x01, 0x89, 0x58, 0x1f, 0x1e, 0xf5, 0xa5, 0x42,
  0x8f, 0x60, 0x2e, 0xc2, 0xd8, 0x21, 0x0b, 0x6c, 0x8d, 0xbb, 0x72, 0xf2,
  0x19, 0x30, 0xe3, 0x4c, 0x3e, 0x80, 0xe7, 0xf2, 0xe3, 0x89, 0x4f, 0xd4,
  0xee, 0x96, 0x3e, 0x4a, 0x9b, 0xe5, 0x16, 0x01, 0xf1, 0x98, 0xc9, 0x0b,
  0xd6, 0xdf, 0x8a, 0x64, 0x47, 0xc4, 0x44, 0xcc, 0x92, 0x69, 0x28, 0xee,
  0x7d, 0xac, 0xdc, 0x30, 0x56, 0x3a, 0xe7, 0xbc, 0xba, 0x45, 0x16, 0x2c,
  0x4c, 0x46, 0x6b, 0x2b, 0x20, 0xfb, 0x3d, 0x20, 0x35, 0xbb, 0x48, 0x49,
  0x13, 0x65, 0xc9, 0x9a, 0x38, 0x10, 0x84, 0x1a, 0x8c, 0xc9, 0xd7, 0xde,
  0x07, 0x10, 0x5a, 0xfb, 0xb4, 0x95, 0xae, 0x18, 0xf2, 0xe3, 0x15, 0xe8,
  0xad, 0x7e, 0xe5, 0x3c, 0xa8, 0x47, 0x85, 0xd6, 0x1f, 0x54, 0xb5, 0xa3,
  0x79, 0x02, 0x03, 0x01, 0x00, 0x01
}; ///< The GBv2 public key file.
static unsigned int __gbv2keypub_der_len = 294; ///< Length of GBv2 public key data

/// Attempts to load the GBv2 public key.
Auth::Auth(){
  const unsigned char * key = __gbv2keypub_der;
  pubkey = d2i_RSAPublicKey(0, &key, __gbv2keypub_der_len);
}

/// Attempts to verify RSA signature using the public key.
/// Assumes basesign argument is base64 encoded RSA signature for data.
/// Returns true if the data could be verified, false otherwise.
bool Auth::PubKey_Check(std::string & data, std::string basesign){
  std::string sign = Base64::decode(basesign);
  return (RSA_verify(NID_md5, (unsigned char*)data.c_str(), data.size(), (unsigned char*)sign.c_str(), sign.size(), pubkey) == 1);
}