#ifndef TIMER_H
#define TIMER_H

#include <SDL2/SDL.h>

class Timer
{
    public:
        Timer();

        // Record the current clock time since program start.
        // Use this to simulate the start or reset of a timer.
        void start();

        // Get the number of seconds since the last call to start()
        float getElapsedSeconds() const;

    private:
        Uint32 start_time;
};

#endif // TIMER_H
