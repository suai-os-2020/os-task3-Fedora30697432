#include "lab3.h"
#include "windows.h"
//
// lab3 code should be located here!
//

#define MAX_SEM_COUNT 13
#define THREADCOUNT 11
#define SEM_COUNT 13

#define SEM_1 10
#define SEM_2 11
#define SEM_3 12



HANDLE sem[SEM_COUNT];
HANDLE mut;
DWORD WINAPI Thread_a(LPVOID);
DWORD WINAPI Thread_b(LPVOID);
DWORD WINAPI Thread_c(LPVOID);
DWORD WINAPI Thread_d(LPVOID);
DWORD WINAPI Thread_e(LPVOID);
DWORD WINAPI Thread_h(LPVOID);
DWORD WINAPI Thread_g(LPVOID);
DWORD WINAPI Thread_i(LPVOID);
DWORD WINAPI Thread_f(LPVOID);
DWORD WINAPI Thread_k(LPVOID);
DWORD WINAPI Thread_m(LPVOID);


unsigned int lab3_thread_graph_id()
{
    return 6;
}

const char* lab3_unsynchronized_threads()
{
    return "deg";
}

const char* lab3_sequential_threads()
{
    return "bcd";
}

int lab3_init()
{
    mut = CreateMutex(NULL, FALSE, "Mutex");
    HANDLE aThread[THREADCOUNT];
    DWORD ThreadID;
    int i;
    sem[0] = CreateSemaphore(NULL, 1, MAX_SEM_COUNT, NULL);
    sem[1] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[2] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[3] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[4] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[5] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[6] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[7] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[8] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[9] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[10] = CreateSemaphore(NULL, 1, MAX_SEM_COUNT, NULL);
    sem[11] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);
    sem[12] = CreateSemaphore(NULL, 0, MAX_SEM_COUNT, NULL);

    for (i = 0; i < SEM_COUNT; i++)
    {
        if (sem[i] == NULL)
        {
            std::cout << "CreateSemaphore error: " << GetLastError() << std::endl;
            return 1;
        }
    }

    aThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_a, NULL, 0, &ThreadID);
    aThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_b, NULL, 0, &ThreadID);
    aThread[2] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_c, NULL, 0, &ThreadID);
    aThread[3] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_d, NULL, 0, &ThreadID);
    aThread[4] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_e, NULL, 0, &ThreadID);
    aThread[5] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_f, NULL, 0, &ThreadID);
    aThread[6] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_g, NULL, 0, &ThreadID);
    aThread[7] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_i, NULL, 0, &ThreadID);
    aThread[8] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_k, NULL, 0, &ThreadID);
    aThread[9] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_m, NULL, 0, &ThreadID);
    aThread[10] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread_h, NULL, 0, &ThreadID);

    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);
    for (i = 0; i < THREADCOUNT; i++)
        CloseHandle(aThread[i]);
    for (i = 0; i < SEM_COUNT; i++)
        CloseHandle(sem[i]);
    CloseHandle(mut);
    return 0;
}

DWORD WINAPI Thread_a(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[0], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'a';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    ReleaseSemaphore(sem[1], 3, NULL);
    return TRUE;
}

DWORD WINAPI Thread_b(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[1], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(sem[SEM_1], INFINITE);
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'b';
        ReleaseMutex(mut);
        sleep_ms(50);
        ReleaseSemaphore(sem[SEM_2], 1, NULL);
    }
    WaitForSingleObject(sem[SEM_1], INFINITE);
    ReleaseSemaphore(sem[2], 1, NULL);
    return TRUE;
}

DWORD WINAPI Thread_c(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[1], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(sem[SEM_2], INFINITE);
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'c';
        ReleaseMutex(mut);
        sleep_ms(50);
        ReleaseSemaphore(sem[SEM_3], 1, NULL);
    }
    WaitForSingleObject(sem[SEM_1], INFINITE);
    ReleaseSemaphore(sem[3], 1, NULL);
    return TRUE;
}

DWORD WINAPI Thread_d(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[1], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(sem[SEM_3], INFINITE);
        WaitForSingleObject(mut, INFINITE);
        std::cout <<'d';
        ReleaseMutex(mut);
        sleep_ms(50);
        ReleaseSemaphore(sem[SEM_1], 1, NULL);
    }
    ReleaseSemaphore(sem[SEM_1], 1, NULL);

    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout <<'d';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    ReleaseSemaphore(sem[4], 2, NULL);
    return TRUE;
}

DWORD WINAPI Thread_e(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[3], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'e';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    ReleaseSemaphore(sem[5], 2, NULL);
    return TRUE;
}

DWORD WINAPI Thread_g(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[2], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 6; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'g';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    ReleaseSemaphore(sem[6], 2, NULL);
    return TRUE;
}

DWORD WINAPI Thread_f(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[4], INFINITE);
    WaitForSingleObject(sem[5], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'f';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    ReleaseSemaphore(sem[7], 2, NULL);
    return TRUE;
}

DWORD WINAPI Thread_h(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[4], INFINITE);
    WaitForSingleObject(sem[5], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 6; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'h';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    ReleaseSemaphore(sem[9], 1, NULL);
    return TRUE;
}

DWORD WINAPI Thread_i(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[6], INFINITE);
    WaitForSingleObject(sem[7], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'i';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    ReleaseSemaphore(sem[8], 1, NULL);
    return TRUE;
}

DWORD WINAPI Thread_k(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[6], INFINITE);
    WaitForSingleObject(sem[7], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 6; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'k';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    return TRUE;
}

DWORD WINAPI Thread_m(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[8], INFINITE);
    WaitForSingleObject(sem[9], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'m';
        ReleaseMutex(mut);
        sleep_ms(50);
    }
    return TRUE;
}
