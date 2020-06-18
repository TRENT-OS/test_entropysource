#include "OS_Crypto.h"
#include "OS_Dataport.h"

#include "TestMacros.h"

#include "LibDebug/Debug.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <camkes.h>

// Public Functions ------------------------------------------------------------

int run()
{
    OS_Crypto_Handle_t hCrypto;
    static OS_Crypto_Config_t cfgDummy =
    {
        .mode = OS_Crypto_MODE_LIBRARY_ONLY,
        .library.entropy = OS_CRYPTO_ASSIGN_EntropySource(entropySource_rpc_read,
                                                          entropySource_dp),
    };
    static OS_Crypto_Config_t cfgOwn =
    {
        .mode = OS_Crypto_MODE_LIBRARY_ONLY,
        .library.entropy = OS_CRYPTO_ASSIGN_EntropySource(myEntropy_rpc_read,
                                                          myEntropy_dp),
    };

    TEST_SUCCESS(OS_Crypto_init(&hCrypto, &cfgDummy));
    TEST_SUCCESS(OS_Crypto_free(hCrypto));

    TEST_SUCCESS(OS_Crypto_init(&hCrypto, &cfgOwn));
    TEST_SUCCESS(OS_Crypto_free(hCrypto));

    Debug_LOG_INFO("All tests successfully completed.");

    return 0;
}