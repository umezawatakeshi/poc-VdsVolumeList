#pragma once

const char* VdsProviderTypeToString(VDS_PROVIDER_TYPE x);
const char* VdsPackStatusToString(VDS_PACK_STATUS x);
const char* VdsVolumeTypeToString(VDS_VOLUME_TYPE x);
const char* VdsVolumeStatusToString(VDS_VOLUME_STATUS x);
std::string VdsVolumeFlagsToStdString(ULONG x);
const char* VdsHealthToString(VDS_HEALTH x);
const char* VdsFileSystemTypeToString(VDS_FILE_SYSTEM_TYPE x);
std::string GuidToStdString(const GUID* x);
