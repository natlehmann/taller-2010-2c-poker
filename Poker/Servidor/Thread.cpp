#include "Thread.h"

bool Thread::CreateNewThread()
{
 m_hThread = CreateThread(NULL, 
                          0, 
                          (LPTHREAD_START_ROUTINE)_ThreadFunc, 
                          (LPVOID) this, 
                          0, 
                          (LPDWORD) &m_lpId);

 if(m_hThread == NULL)
  return false;

 m_bActive = true;
 return true;
}

bool Thread::Suspend()
{
 m_bActive = false;
 return(-1 != SuspendThread(m_hThread));//win32 API         
}

bool Thread::Kill()
{
 return (TerminateThread(m_hThread, 1) != 0); //win32 API
}
 
bool Thread::Resume()
{
 m_bActive = true;
 return(-1 != ResumeThread(m_hThread)); //win32 API
}

bool Thread::Wait()
{
 return (WAIT_OBJECT_0 == WaitForSingleObject(m_hThread, INFINITE)); //win32 API
}

bool Thread::IsActive()
{
 return m_bActive;
}
