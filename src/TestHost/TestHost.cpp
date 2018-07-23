// TestHost.cpp : Defines the entry point for the console application.
//

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <HidCerberus.h>
#include <stdio.h>
#include <iostream>

EVT_HC_PROCESS_ACCESS_REQUEST ProcessAccessRequest;

int main()
{
    auto handle = hc_init();

    hc_register_access_request_event(handle, ProcessAccessRequest);

    getchar();

    hc_shutdown(handle);

    return 0;
}

BOOL ProcessAccessRequest(
    PHC_ARE_HANDLE Handle,
    PCSTR HardwareIds[],
    ULONG HardwareIdsCount,
    PCSTR DeviceId,
    PCSTR InstanceId,
    DWORD ProcessId
)
{
    for (unsigned int i = 0; i < HardwareIdsCount; i++)
    {
        std::cout << HardwareIds[i] << ": " << DeviceId << " " << InstanceId << std::endl;
    }

    hc_submit_access_request_result(Handle, TRUE, FALSE);

    return TRUE;
}
