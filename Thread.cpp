#include "Thread.h"

Thread::Thread() : mRunning(false)
{
}

bool Thread::start()
{
    // do not start the thread if it is already running
    if (mRunning) return 0;

    mThread = SDL_CreateThread(Thread::threadFunction, (void*) this);
    if (mThread == NULL) return false;
    return true;
}

void Thread::stop()
{
    // thread-stopping has to be manually supported by the child class (if is to
    // be supported at all)
}

void Thread::stopAndWait()
{
    stop();
    while (mRunning) SDL_Delay(1);
}

int Thread::threadFunction(void* inData)
{
    Thread* t = (Thread*) inData;
    t->mRunning = true;
    t->run();
    t->mRunning = false;
    return 0;
}

bool Thread::isRunning()
{
    return mRunning;
}
