#include "Timer.h"

Timer::Timer() : start_time(0)
{}

void Timer::start(){
    start_time = SDL_GetTicks();
}

float Timer::getElapsedSeconds() const{

    // Get the elapsed time since the call of start() in milliseconds
    float milli = SDL_GetTicks() - start_time;

    // Convert to seconds
    return milli / 1000;
}
