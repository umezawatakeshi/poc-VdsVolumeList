#include "stdafx.h"

#include "EnumToString.h"

const char* VdsProviderTypeToString(VDS_PROVIDER_TYPE x)
{
	switch (x)
	{
	case VDS_PT_UNKNOWN:
		return "Unknown";
	case VDS_PT_SOFTWARE:
		return "Software";
	case VDS_PT_HARDWARE:
		return "Hardware";
	case VDS_PT_VIRTUALDISK:
		return "Virtual Disk";
	default:
		return "Not Defined";
	}
}

const char* VdsPackStatusToString(VDS_PACK_STATUS x)
{
	switch (x)
	{
	case VDS_PS_UNKNOWN:
		return "Unknown";
	case VDS_PS_ONLINE:
		return "Online";
	case VDS_PS_OFFLINE:
		return "Offline";
	default:
		return "Not Defined";
	}
}

const char* VdsVolumeTypeToString(VDS_VOLUME_TYPE x)
{
	switch (x)
	{
	case VDS_VT_UNKNOWN:
		return "Unknown";
	case VDS_VT_SIMPLE:
		return "Simple";
	case VDS_VT_SPAN:
		return "Span";
	case VDS_VT_STRIPE:
		return "Stripe";
	case VDS_VT_MIRROR:
		return "Mirror";
	case VDS_VT_PARITY:
		return "Parity";
	default:
		return "Not Defined";
	}
}

const char* VdsVolumeStatusToString(VDS_VOLUME_STATUS x)
{
	switch (x)
	{
	case VDS_VS_UNKNOWN:
		return "Unknown";
	case VDS_VS_ONLINE:
		return "Online";
	case VDS_VS_NO_MEDIA:
		return "No Media";
	case VDS_VS_OFFLINE:
		return "Offline";
	case VDS_VS_FAILED:
		return "Failed";
	default:
		return "Not Defined";
	}
}

std::string VdsVolumeFlagsToStdString(ULONG x)
{
	char buf[512] = "";
	if (x & VDS_VF_SYSTEM_VOLUME)
		strcat(buf, ",System");
	if (x & VDS_VF_BOOT_VOLUME)
		strcat(buf, ",Boot");
	if (x & VDS_VF_ACTIVE)
		strcat(buf, ",Active");
	if (x & VDS_VF_READONLY)
		strcat(buf, ",ReadOnly");
	if (x & VDS_VF_HIDDEN)
		strcat(buf, ",Hidden");
	if (x & VDS_VF_CAN_EXTEND)
		strcat(buf, ",CanExtend");
	if (x & VDS_VF_CAN_SHRINK)
		strcat(buf, ",CanShrink");
	if (x & VDS_VF_PAGEFILE)
		strcat(buf, ",PageFile");
	if (x & VDS_VF_HIBERNATION)
		strcat(buf, ",Hibernation");
	if (x & VDS_VF_CRASHDUMP)
		strcat(buf, ",CrashDump");
	if (x & VDS_VF_INSTALLABLE)
		strcat(buf, ",Installable");
	if (x & VDS_VF_LBN_REMAP_ENABLED)
		strcat(buf, ",LbnRemapEnabled");
	if (x & VDS_VF_FORMATTING)
		strcat(buf, ",Formatting");
	if (x & VDS_VF_NOT_FORMATTABLE)
		strcat(buf, ",NotFormattable");
	if (x & VDS_VF_NTFS_NOT_SUPPORTED)
		strcat(buf, ",NtfsNotSupported");
	if (x & VDS_VF_FAT32_NOT_SUPPORTED)
		strcat(buf, ",Fat32NotSupported");
	if (x & VDS_VF_FAT_NOT_SUPPORTED)
		strcat(buf, ",FatNotSupported");
	if (x & VDS_VF_NO_DEFAULT_DRIVE_LETTER)
		strcat(buf, ",NoDefaultDriveLetter");
	if (x & VDS_VF_PERMANENTLY_DISMOUNTED)
		strcat(buf, ",PermanentlyDismounted");
	if (x & VDS_VF_PERMANENT_DISMOUNT_SUPPORTED)
		strcat(buf, ",PermanentDismountSupported");
	if (x & VDS_VF_SHADOW_COPY)
		strcat(buf, ",ShadowCopy");
	if (x & VDS_VF_REFS_NOT_SUPPORTED)
		strcat(buf, ",RefsNotSupported");
	if (x & VDS_VF_BACKS_BOOT_VOLUME)
		strcat(buf, ",BacksBootVolume");
	if (x & VDS_VF_BACKED_BY_WIM_IMAGE)
		strcat(buf, ",BackedByWimImage");

	return buf[0] ? buf + 1 : "";
}

const char* VdsHealthToString(VDS_HEALTH x)
{
	switch (x)
	{
	case VDS_H_UNKNOWN:
		return "Unknown";
	case VDS_H_HEALTHY:
		return "Healthy";
	case VDS_H_REBUILDING:
		return "Rebuilding";
	case VDS_H_STALE:
		return "Stale";
	case VDS_H_FAILING:
		return "Failing";
	case VDS_H_FAILING_REDUNDANCY:
		return "FailingRedundancy";
	case VDS_H_FAILED_REDUNDANCY:
		return "FailedRedundancy";
	case VDS_H_FAILED_REDUNDANCY_FAILING:
		return "FailedRedundancyFailing";
	case VDS_H_FAILED:
		return "Failed";
	case VDS_H_REPLACED:
		return "Replaced";
	case VDS_H_PENDING_FAILURE:
		return "PendingFailure";
	case VDS_H_DEGRADED:
		return "Degraded";
	default:
		return "Not Defined";
	}
}

const char* VdsFileSystemTypeToString(VDS_FILE_SYSTEM_TYPE x)
{
	switch (x)
	{
	case VDS_FST_UNKNOWN:
		return "Unknown";
	case VDS_FST_RAW:
		return "Raw";
	case VDS_FST_FAT:
		return "FAT";
	case VDS_FST_FAT32:
		return "FAT32";
	case VDS_FST_NTFS:
		return "NTFS";
	case VDS_FST_CDFS:
		return "CDFS";
	case VDS_FST_UDF:
		return "UDF";
	case VDS_FST_EXFAT:
		return "exFAT";
	case VDS_FST_CSVFS:
		return "CSVFS";
	case VDS_FST_REFS:
		return "ReFS";
	default:
		return "Not Defined";
	}
}

std::string GuidToStdString(const GUID* x)
{
	RPC_CSTR buf;
	UuidToStringA(x, &buf);
	return reinterpret_cast<const char*>(buf);
}
