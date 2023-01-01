#include "stdafx.h"

#include "EnumToString.h"

_COM_SMARTPTR_TYPEDEF(IVdsServiceLoader, IID_IVdsServiceLoader);
_COM_SMARTPTR_TYPEDEF(IVdsService, IID_IVdsService);
_COM_SMARTPTR_TYPEDEF(IEnumVdsObject, IID_IEnumVdsObject);
_COM_SMARTPTR_TYPEDEF(IVdsProvider, IID_IVdsProvider);
_COM_SMARTPTR_TYPEDEF(IVdsSwProvider, IID_IVdsSwProvider);
_COM_SMARTPTR_TYPEDEF(IVdsPack, IID_IVdsPack);
_COM_SMARTPTR_TYPEDEF(IVdsVolume, IID_IVdsVolume);
_COM_SMARTPTR_TYPEDEF(IVdsVolumeMF, IID_IVdsVolumeMF);

int main()
{
	IVdsServiceLoaderPtr pServiceLoader;
	IVdsServicePtr pService;
	IEnumVdsObjectPtr pEnumVdsProvider;
	IUnknownPtr pUnknown;
	ULONG cFetched;
	HRESULT hr;

	CoInitialize(NULL);

	pServiceLoader.CreateInstance(CLSID_VdsLoader, NULL, CLSCTX_LOCAL_SERVER);
	pServiceLoader->LoadService(NULL, &pService);
	pService->WaitForServiceReady();
	pService->QueryProviders(VDS_QUERY_SOFTWARE_PROVIDERS, &pEnumVdsProvider);
	while (pEnumVdsProvider->Next(1, &pUnknown, &cFetched) == S_OK)
	{
		IVdsProviderPtr pVdsProvider = pUnknown;
		pUnknown = NULL;
		VDS_PROVIDER_PROP provider;
		pVdsProvider->GetProperties(&provider);
		printf("id=%s name=\"%S\" type=%s\n",
			GuidToStdString(&provider.id).c_str(),
			provider.pwszName,
			VdsProviderTypeToString(provider.type));
		switch (provider.type)
		{
		case VDS_PT_SOFTWARE:
			{
				IVdsSwProviderPtr pVdsSwProvider = pVdsProvider;
				pVdsProvider = NULL;
				IEnumVdsObjectPtr pEnumVdsPack;
				pVdsSwProvider->QueryPacks(&pEnumVdsPack);
				while (pEnumVdsPack->Next(1, &pUnknown, &cFetched) == S_OK)
				{
					IVdsPackPtr pVdsPack = pUnknown;
					pUnknown = NULL;
					VDS_PACK_PROP pack;
					pVdsPack->GetProperties(&pack);
					printf("  id=%s name=\"%S\" status=%s\n",
						GuidToStdString(&pack.id).c_str(),
						pack.pwszName,
						VdsPackStatusToString(pack.status));

					IEnumVdsObjectPtr pEnumVolume;
					pVdsPack->QueryVolumes(&pEnumVolume);
					while (pEnumVolume->Next(1, &pUnknown, &cFetched) == S_OK)
					{
						IVdsVolumePtr pVdsVolume = pUnknown;
						pUnknown = NULL;
						VDS_VOLUME_PROP volume;
						pVdsVolume->GetProperties(&volume);
						printf("    id=%s name=\"%S\" type=%s status=%s health=%s fs=%s",
							GuidToStdString(&volume.id).c_str(),
							volume.pwszName,
							VdsVolumeTypeToString(volume.type),
							VdsVolumeStatusToString(volume.status),
							VdsHealthToString(volume.health),
							VdsFileSystemTypeToString(volume.RecommendedFileSystemType));

						IVdsVolumeMFPtr pVdsVolumeMF = pVdsVolume;
						VDS_FILE_SYSTEM_PROP fs;
						hr = pVdsVolumeMF->GetFileSystemProperties(&fs);
						if (SUCCEEDED(hr)) // for example, CD-ROM volume returns error without media.
						{
							// workaround for non-ascii volume labels.
							// printf's %S and wprintf's %s don't seem to support non-ascii wide characters.
							char buf[256];
							wsprintfA(buf, " label=\"%S\"", fs.pwszLabel ? fs.pwszLabel : L"(null)");
							printf("%s", buf);
						}
						LPWSTR* pwszAccessPathArray;
						LONG lNumberOfResults;
						pVdsVolumeMF->QueryAccessPaths(&pwszAccessPathArray, &lNumberOfResults);
						for (LONG i = 0; i < lNumberOfResults; ++i)
							printf(" path=%S", pwszAccessPathArray[i]);
						VDS_REPARSE_POINT_PROP* pReparsePointArray;
						pVdsVolumeMF->QueryReparsePoints(&pReparsePointArray, &lNumberOfResults);
						for (LONG i = 0; i < lNumberOfResults; ++i)
							printf(" reparse=%s/%S",
								GuidToStdString(&pReparsePointArray[i].SourceVolumeId).c_str(),
								pReparsePointArray[i].pwszPath);
						printf(" flags=%s", VdsVolumeFlagsToStdString(volume.ulFlags).c_str());
						printf("\n");
					}
				}
			}
		}
	}
}
