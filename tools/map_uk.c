/**
 ******************************************************************************
 * @file    ossocket.c
 * @brief    Linux和Windows环境下通用互斥量

代码来源：《Cross Platform Mutex》\n
http://www.codeproject.com/Articles/25569/Cross-Platform-Mutex
原始版本均采用互斥量来同步线程，鉴于Windows环境下互斥量是内核结构，访问开销
大，可能我会在调试IOCP时将其改成临界区
 *
|     Version    |     Author        |      Date      |    Content   
| :------------: | :---------------: | :------------: | :------------
|     V1.0       |    Gulyan         |   2008-xx-xx   | 1.Cross Platform Mutex    
|                |                   |                | 2.linux(Mutex),Windows(Mutex)
|     V1.1Bate   |    Menglong Wu    |   2015-01-16   | 1.MUTEX_TRYLOCK
|                |                   |                | 2.Windows(Mutex) Chance Windows(CriticalSection)
 * @attention
 *
 * ATTENTION
 *
 * <h2><center>&copy; COPYRIGHT </center></h2>
*/


#include <ossocket.h>

int MUTEX_INIT(OS_MUTEX *mutex)
{
    #if defined(LINUX)
        return pthread_mutex_init (mutex, NULL);;
    #elif defined(WINDOWS)
        *mutex = CreateMutex(0, FALSE, 0);;
        return (*mutex==0);
    #endif
    return -1;
}

int MUTEX_LOCK(OS_MUTEX *mutex)
{
    #if defined(LINUX)
        return pthread_mutex_lock( mutex );
    #elif defined(WINDOWS)
        return (WaitForSingleObject(*mutex, INFINITE)==WAIT_FAILED?1:0);
    #endif
    return -1;
}

int MUTEX_TRYLOCK(OS_MUTEX *mutex)
{
    #if defined(LINUX)
        return pthread_mutex_trylock(mutex);
    #elif defined(WINDOWS)
        //TODO Windows API 
        //return (TryEnterCriticalSection(mutex) == 0? 1: 0);
    #endif
    return -1;
}

int MUTEX_UNLOCK(OS_MUTEX *mutex)
{
    #if defined(LINUX)
        return pthread_mutex_unlock( mutex );
    #elif defined(WINDOWS)
        return (ReleaseMutex(*mutex)==0);
    #endif
    return -1;
}
                                �%�1h�   �P����%�1h�   �@����%�1h�   �0����%�1h�   � ����%�1h�   �����%�1h�   � ����%�1h�   ������%�1h   ������%�1h  ������%�1h  ������%�1h  �����%�1h   �����%�1h(  �����%�1h0  �����%�1h8  �p����%�1h@  �`����%�1hH  �P����%�1hP  �@����% 2hX  �0����%2h`  � ����%2hh  �����%2hp  � ����%2hx  ������%2h�  ������%2h�  ������%2h�  ������% 2h�  �����%$2h�  �����%(2h�  �����%,2h�  �����%02h�  �p����%42h�  �`����%82h�  �P����%<2h�  �@����%@2h�  �0����%D2h�  � ����%H2h�  �����%L2h�  � ����%P2h�  ������%T2h   ������%X2h  ������%\2h  ������%`2h  �����%d2h   �����%h2h(  �����%l2h0  �����%p2h8  �p����%t2h@  �`����%x2hH  �P����%|2hP  �@����%�2hX  �0����%�2h`  � ����%�2hh  �����%�2hp  � ����%�2hx  ������%�2h�  ������%�2h�  ������%�2h�  ������%�2h�  �����%�2h�  �����%�2h�  �����%�2h�  �����%�2h�  �p����%�2h�  �`����%�2h�  �P����%�2h�  �@����%�2h�  �0����%�2h�  � ���