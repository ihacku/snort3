//--------------------------------------------------------------------------
// Copyright (C) 2014-2018 Cisco and/or its affiliates. All rights reserved.
// Copyright (C) 2005-2013 Sourcefire, Inc.
//
// This program is free software; you can redistribute it and/or modify it
// under the terms of the GNU General Public License Version 2 as published
// by the Free Software Foundation.  You may not use, modify or distribute
// this program under any other version of the GNU General Public License.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// General Public License for more details.
//
// You should have received a copy of the GNU General Public License along
// with this program; if not, write to the Free Software Foundation, Inc.,
// 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
//--------------------------------------------------------------------------

// length_app_cache.cc author Sourcefire Inc.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "length_app_cache.h"

#include "application_ids.h"
#include "hash/xhash.h"
#include "log/messages.h"
#include "main/thread.h"

#define HASH_NUM_ROWS (1024)

static THREAD_LOCAL XHash* lengthCache = nullptr;

void init_length_app_cache()
{
    if (!(lengthCache = xhash_new(HASH_NUM_ROWS, sizeof(LengthKey), sizeof(AppId),
            0, 0, nullptr, nullptr, 0)))
    {
        ErrorMessage("lengthAppCache: Failed to allocate length cache!");
    }
}

void free_length_app_cache()
{
    if (lengthCache)
    {
        xhash_delete(lengthCache);
        lengthCache = nullptr;
    }
}

AppId find_length_app_cache(const LengthKey* key)
{
    AppId* val = (AppId*)xhash_find(lengthCache, (void*)key);
    if (val == nullptr)
        return APP_ID_NONE;    /* no match */
    else
        return *val;           /* match found */
}

bool add_length_app_cache(const LengthKey* key, AppId val)
{
    if (xhash_add(lengthCache, (void*)key, (void*)&val))
    {
        return false;
    }
    return true;
}

