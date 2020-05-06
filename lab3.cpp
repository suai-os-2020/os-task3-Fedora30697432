#include "lab3.h"
#include "windows.h"
//
// lab3 code should be located here!
//


// Максимальное значение счётчика у семаформа
#define MAX_SEM_COUNT 13
// Число потоков
#define THREADCOUNT 11
// Число семафоров
#define SEM_COUNT 13


// Вспомогательные определения.
#define SEM_1 10
#define SEM_2 11
#define SEM_3 12


// Массив семафоров
HANDLE sem[SEM_COUNT];
// Мьютекс
HANDLE mut;

// Прототипы потоков
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
    // Создание мьютека. Первое значение "атрибут безопасности" имеет значение NULL, т.е. у нас его нет.
    // Второе значение 'FALSE' означает, что мьютекс не будет использован сразу же в данном потоке.
    // Третье значение обозначает имя объекта
    mut = CreateMutex(NULL, FALSE, "Mutex");
    // Массив потоков.
    HANDLE aThread[THREADCOUNT];

    // ID потока
    DWORD ThreadID;
    int i;

    // Инифиализация семафора. Перове значение имееет тот же смысл, что и в инициализации мьютекса.
    // Второе значение это начальное значение счётчика семафора.
    // Третье значение это максимальное значение счётчика семафора.
    // Четвёртое значение означает адрес имени объекта Semaphore. Оно нам не нужно, поэтому имеет значение NULL.
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

    //Проверка на отсутствие ошибок при создании семафоров.
    for (i = 0; i < SEM_COUNT; i++)
    {
        if (sem[i] == NULL)
        {
            std::cout << "CreateSemaphore error: " << GetLastError() << std::endl;
            return 1;
        }
    }

    // Инициализация потоков. Первое значение называется "дескриптор защиты". Мы не собираемся создавать дочерние потоки, поэтому оставляем NULL.
    // Второе значение это размер стека. 0 означает использовать стандартное значение в 1 мб.
    // Третье значение это адрес функции, которую будет выполнять поток.
    // Четвёртое значение это указатель на переменную, которую собираемся передавать в поток. Так как мы ничего не собираемся передавать, то оставляем NULL.
    // Пятое значение обозначает флаги создания. Мы собираемя запускать поток сразу же, поэтому оставляем 0.
    // Шестое значение - указатель на переменную, куда будет сохранён ID потока.
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

    // Данна функция приостанавливает выполение данного потока, пока все потоки из массива не будут завершены.
    // Первое значение - колличество потоков в массиве. Второе значение - сам массив с потоками.
    // Третье означает, что мы собираемся ждать завершения всех потоков
    // Четвёртое знаечние - максимальное время ожидания. Мы собираемся ждать бесконечно, пока потоки не завершатся
    WaitForMultipleObjects(THREADCOUNT, aThread, TRUE, INFINITE);

    // Высвобождение ресурсов.
    for (i = 0; i < THREADCOUNT; i++)
        CloseHandle(aThread[i]);
    for (i = 0; i < SEM_COUNT; i++)
        CloseHandle(sem[i]);
    CloseHandle(mut);
    return 0;
}



DWORD WINAPI Thread_a(LPVOID lpParam)
{
    // Данный макрос говорит о том, что мы не используем входной параметр
    UNREFERENCED_PARAMETER(lpParam);
    // Ожидание пока счётчик семафора (sem[0]) будет > 0. Как только данное условие будет выполнено, счётчик уменьшится на 1
    // и поток продолжит выполнение инструкций. Второе значение говорит о том, что здать мы будем бесконечно.
    WaitForSingleObject(sem[0], INFINITE);

    // Открываем мьютекс. Требуемый доступ SYNCHRONIZE, флаг наследования = false, находим мьютекс по имени "Mutex"
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        // Ждём когда мьютекс будет свободен (=1). Как только выполнится данное условие, мьютекс заблокируется (счётчик мьютекс уменьшится на 1)
        // и мы войдём в критическую секцию. Ждём бесконечно.
        WaitForSingleObject(mut, INFINITE);
        // Выводим на экран букву.
        std::cout<<'a';
        // Высвобождаем мьютекс (увеличиваем счётчик на 1), чтобы другие потоки могли воспользоваться критической секцией.
        ReleaseMutex(mut);
        // Выполнияем вычисления
        computation();
    }
    // Увеличиваем счётчик семафора sem[1] на 3. Предыдущее значение счётчика NULL.
    ReleaseSemaphore(sem[1], 3, NULL);
    // Завершение потока.
    return TRUE;
}

DWORD WINAPI Thread_b(LPVOID lpParam)
{
    // Данный макрос говорит о том, что мы не используем входной параметр
    UNREFERENCED_PARAMETER(lpParam);
    // Ожидание пока счётчик семафора (sem[1]) будет > 0. Как только данное условие будет выполнено, счётчик уменьшится на 1
    // и поток продолжит выполнение инструкций. Второе значение говорит о том, что здать мы будем бесконечно.
    WaitForSingleObject(sem[1], INFINITE);
    // Открываем мьютекс. Требуемый доступ SYNCHRONIZE, флаг наследования = false, находим мьютекс по имени "Mutex"
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        // Ожидание пока счётчик семафора sem[SEM_1] будет > 0. Как только данное условие будет выполнено, счётчик уменьшится на 1
        // и поток продолжит выполнение инструкций. Второе значение говорит о том, что здать мы будем бесконечно.
        WaitForSingleObject(sem[SEM_1], INFINITE);
        // Ждём когда мьютекс будет свободен (=1). Как только выполнится данное условие, мьютекс заблокируется (счётчик мьютекс уменьшится на 1)
        // и мы войдём в критическую секцию. Ждём бесконечно.
        WaitForSingleObject(mut, INFINITE);
        // Выводим на экран букву.
        std::cout<<'b';
        // Высвобождаем мьютекс (увеличиваем счётчик на 1), чтобы другие потоки могли воспользоваться критической секцией.
        ReleaseMutex(mut);
        // Выполнияем вычисления
        computation();
        // Увеличиваем счётчик семафора sem[SEM_2] на 1. Предыдущее значение счётчика NULL.
        ReleaseSemaphore(sem[SEM_2], 1, NULL);
    }
    // Ожидание пока счётчик семафора (sem[SEM_1]) будет > 0. Как только данное условие будет выполнено, счётчик уменьшится на 1
    // и поток продолжит выполнение инструкций. Второе значение говорит о том, что здать мы будем бесконечно.
    WaitForSingleObject(sem[SEM_1], INFINITE);
    // Увеличиваем счётчик семафора sem[2] на 1. Предыдущее значение счётчика NULL.
    ReleaseSemaphore(sem[2], 1, NULL);
    // Завершение потока.
    return TRUE;
}

// Остальные функции выполняются аналогично.

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
        computation();
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
        computation();
        ReleaseSemaphore(sem[SEM_1], 1, NULL);
    }
    ReleaseSemaphore(sem[SEM_1], 1, NULL);

    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout <<'d';
        ReleaseMutex(mut);
        computation();
    }
    ReleaseSemaphore(sem[4], 3, NULL);
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
        computation();
    }
    ReleaseSemaphore(sem[5], 3, NULL);
    return TRUE;
}

DWORD WINAPI Thread_g(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[2], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'g';
        ReleaseMutex(mut);
        computation();
    }
    ReleaseSemaphore(sem[6], 2, NULL);
    WaitForSingleObject(sem[4], INFINITE);
    WaitForSingleObject(sem[5], INFINITE);
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'g';
        ReleaseMutex(mut);
        computation();
    }
    ReleaseSemaphore(sem[6], 3, NULL);
    return TRUE;
}

DWORD WINAPI Thread_f(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[6], INFINITE);
    WaitForSingleObject(sem[4], INFINITE);
    WaitForSingleObject(sem[5], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'f';
        ReleaseMutex(mut);
        computation();
    }
    ReleaseSemaphore(sem[7], 3, NULL);
    return TRUE;
}

DWORD WINAPI Thread_h(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[6], INFINITE);
    WaitForSingleObject(sem[4], INFINITE);
    WaitForSingleObject(sem[5], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'h';
        ReleaseMutex(mut);
        computation();
    }
    ReleaseSemaphore(sem[9], 2, NULL);
    WaitForSingleObject(sem[7], INFINITE);
    WaitForSingleObject(sem[6], INFINITE);
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'h';
        ReleaseMutex(mut);
        computation();
    }
    ReleaseSemaphore(sem[9], 1, NULL);
    return TRUE;
}

DWORD WINAPI Thread_i(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[6], INFINITE);
    WaitForSingleObject(sem[7], INFINITE);
    WaitForSingleObject(sem[9], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'i';
        ReleaseMutex(mut);
        computation();
    }
    ReleaseSemaphore(sem[8], 2, NULL);
    return TRUE;
}

DWORD WINAPI Thread_k(LPVOID lpParam)
{
    UNREFERENCED_PARAMETER(lpParam);
    WaitForSingleObject(sem[6], INFINITE);
    WaitForSingleObject(sem[7], INFINITE);
    WaitForSingleObject(sem[9], INFINITE);
    mut = OpenMutex(SYNCHRONIZE, false, (LPCSTR)"Mutex");
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'k';
        ReleaseMutex(mut);
        computation();
    }
    WaitForSingleObject(sem[8], INFINITE);
    for (int i = 0; i < 3; i++)
    {
        WaitForSingleObject(mut, INFINITE);
        std::cout<<'k';
        ReleaseMutex(mut);
        computation();
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
        computation();
    }
    return TRUE;
}
