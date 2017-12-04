# CascLibPlus [![License][license-svg]][license-url]

[license-svg]: https://img.shields.io/badge/license-MIT-blue.svg
[license-url]: LICENSE

An open-source object-oriented API for Ladislav Zezula's [CascLib](https://github.com/ladislav-zezula/CascLib) library using C++11 language features. Key benefits are:
* Less boilerplate with RAII semantics.
* Transparent handling of 64-bit integer types.
* Practically zero-cost abstraction.

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

## Overview

### `CascStorage`

Encapsulates the state of a storage handle.

### `CascFile`

Encapsulates both the `CASC_FIND_DATA` data structure and the corresponding file handle. `CascFile` objects are obtained through explicit open methods on `CascStorage` (i.e. `OpenFileByKey`, `OpenFileByEncoding`, `OpenFile`) or via the iterator helpers, `CascIterator` and `CascRange`.

### `CascIterator` and `CascRange`

Enables iteration over files in the `CascStorage` object using C++11's ranged-based for loop syntax. You should not need to manipulate these classes directly.
