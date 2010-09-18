#ifndef THREAD_H_
#define THREAD_H_
#include <windows.h>

class Thread
{
protected:
	HANDLE m_hThread; //Thread handle
	bool m_bActive; //activity indicator
	DWORD m_lpId; //Thread ID

public:
	Thread(){}
	virtual ~Thread(){Kill();}

	//Thread Management
	bool CreateNewThread();
	bool Wait(); //Wait for thread to end
	bool Suspend(); //Suspend the thread
	bool Resume(); //Resume a suspended thread
	bool Kill(); //Terminate a thread
	bool IsActive(); //Check for activity

	//override these functions in the derived class 
	virtual void ThreadEntry(){ }
	virtual void ThreadExit(){ }
	virtual void Run(){ }

	//a friend
	//friend DWORD  WINAPI _ThreadFunc(LPVOID  pvThread);
	//Friend of Thread class
//Actual thread around which the OO wrapper is built.
//Do not call twice on the same object.
//do something (initializing and finalizing) in ThreadEntry and ThreadExit functions.
	friend DWORD WINAPI _ThreadFunc(LPVOID  pvThread)
	{
	 Thread* pThread = (Thread*)pvThread;  //typecast

	 pThread->ThreadEntry(); //initialize
	 pThread->Run();
	 pThread->ThreadExit(); //finalize

	 return 0;
	};

};

#endif /*THREAD_H_*/
