/*
 *  Implementation of EntropySource
 *
 *  Copyright (C) 2020, Hensoldt Cyber GmbH
 */

#include "OS_Dataport.h"

#include <stddef.h>
#include <string.h>

#include <camkes.h>

static OS_Dataport_t port = OS_DATAPORT_ASSIGN(entropySource_dp);

//------------------------------------------------------------------------------
// Interface EntropySource
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
size_t
entropySource_rpc_read(
    const size_t len)
{
    size_t sz;

    // Make sure we don't exceed the dataport len
    sz = OS_Dataport_getSize(port);
    sz = len > sz ? sz : len;

    // Dummy operation; at some point we need to actually use the HW's RNG to
    // fill the buffer
    memset(OS_Dataport_getBuf(port), 0x00, sz);

    return sz;
}