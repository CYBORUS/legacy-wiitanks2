#ifndef _THREAD_H
#define	_THREAD_H

#include <SDL.h>

/**
 * The Thread class is made to simplify the thread creation process and to mimic
 * the Java style of thread handling.
 */
class Thread
{
    public:
        Thread();

        virtual void run() = 0;
        virtual void stop();
        void stopAndWait();
        bool start();
        bool isRunning();
    private:
        static int threadFunction(void *inData);
        volatile bool mRunning;
        SDL_Thread* mThread;
};

#endif
