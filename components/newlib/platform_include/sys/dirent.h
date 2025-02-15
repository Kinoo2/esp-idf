// Copyright 2015-2016 Espressif Systems (Shanghai) PTE LTD
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#pragma once

#include <stddef.h>
#include <stdint.h>

/**
 * This header file provides POSIX-compatible definitions of directory
 * access functions and related data types.
 * See http://pubs.opengroup.org/onlinepubs/7908799/xsh/dirent.h.html
 * for reference.
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Opaque directory structure
 */
typedef struct {
    uint16_t dd_vfs_idx; /*!< VFS index, not to be used by applications */
    uint16_t dd_rsv;     /*!< field reserved for future extension */
    /* remaining fields are defined by VFS implementation */
} DIR;

/**
 * @brief Directory entry structure
 */
struct dirent {
    int d_ino;          /*!< file number */
    uint8_t d_type;     /*!< not defined in POSIX, but present in BSD and Linux */
#define DT_UNKNOWN  0
#define DT_REG      1
#define DT_DIR      2
#if __BSD_VISIBLE
#define MAXNAMLEN 255
    char d_name[MAXNAMLEN+1];   /*!< zero-terminated file name */
#else
    char d_name[256];
#endif
};

DIR* opendir(const char* name);
struct dirent* readdir(DIR* pdir);
long telldir(DIR* pdir);
void seekdir(DIR* pdir, long loc);
void rewinddir(DIR* pdir);
int closedir(DIR* pdir);
int readdir_r(DIR* pdir, struct dirent* entry, struct dirent** out_dirent);

#ifdef __cplusplus
}
#endif

