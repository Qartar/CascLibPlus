// CascStorage.cpp
//

#include "CascStorage.hpp"

//------------------------------------------------------------------------------
CascStorage::CascStorage(TCHAR const* szDataPath, DWORD dwLocaleMask)
    : _storage(NULL)
{
    CascOpenStorage(szDataPath, dwLocaleMask, &_storage);
}

//------------------------------------------------------------------------------
CascStorage::~CascStorage()
{
    if (_storage != NULL) {
        CascCloseStorage(_storage);
    }
}

//------------------------------------------------------------------------------
bool CascStorage::GetStorageInfo(CASC_STORAGE_INFO_CLASS InfoClass, void* pvStorageInfo, size_t cbStorageInfo, size_t* pcbLengthNeeded)
{
    return CascGetStorageInfo(_storage, InfoClass, pvStorageInfo, cbStorageInfo, pcbLengthNeeded);
}

//------------------------------------------------------------------------------
bool CascStorage::AddEncryptionKey(ULONGLONG KeyName, LPBYTE Key)
{
    return CascAddEncryptionKey(_storage, KeyName, Key);
}

//------------------------------------------------------------------------------
CascFile CascStorage::OpenFileByEKey(PQUERY_KEY pCKey, PQUERY_KEY pEKey, DWORD dwOpenFlags, DWORD dwEncodedSize)
{
    HANDLE hFile;
    if (CascOpenFileByEKey(_storage, pCKey, pEKey, dwOpenFlags, dwEncodedSize, &hFile)) {
        return CascFile(hFile);
    } else {
        return CascFile(NULL);
    }
}

//------------------------------------------------------------------------------
CascFile CascStorage::OpenFileByCKey(PQUERY_KEY pCKey, DWORD dwOpenFlags)
{
    HANDLE hFile;
    if (CascOpenFileByCKey(_storage, pCKey, dwOpenFlags, &hFile)) {
        return CascFile(hFile);
    } else {
        return CascFile(NULL);
    }
}

//------------------------------------------------------------------------------
CascFile CascStorage::OpenFile(char const* szFileName, DWORD dwLocale, DWORD dwFlags)
{
    HANDLE hFile;
    if (CascOpenFile(_storage, szFileName, dwLocale, dwFlags, &hFile)) {
        return CascFile(hFile);
    } else {
        return CascFile(NULL);
    }
}

//------------------------------------------------------------------------------
DWORD CascStorage::GetFileId(char const* szFileName)
{
    return CascGetFileId(_storage, szFileName);
}

//------------------------------------------------------------------------------
CascFindFiles CascStorage::FindFiles(char const* szMask, TCHAR const* szListFile)
{
    return CascFindFiles(_storage, szMask, szListFile);
}
