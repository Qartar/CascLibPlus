# CascLibPlus [![License][license-svg]][license-url]

[license-svg]: https://img.shields.io/badge/license-MIT-blue.svg
[license-url]: LICENSE

An open-source object-oriented API for Ladislav Zezula's CascLib library.

## Usage

#### CascLibPlus:

```
CascStorage Storage(szDataPath, dwLocaleMask);
for (CascFile& File : Storage.FindFiles(szMask, szListFile)) {
    // ...
}
```

#### CascLib:

```
HANDLE hStorage = NULL;

if (CascOpenStorage(szDataPath, dwLocaleMask, &hStorage)) {
    CASC_FIND_DATA FindData;

    HANDLE hFile = CascFindFirstFile(hStorage, szMask, &FindData, szListFile);
    if (hFile) {
        do {
            // ...
        } while (CascFindNextFile(hFile, &FindData));

        CascFindClose(hFile);
    }

    CascCloseStorage(hStorage);
}
```
