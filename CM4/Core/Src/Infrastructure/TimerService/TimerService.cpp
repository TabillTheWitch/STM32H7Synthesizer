#include "TimerService.h"

using namespace infrastructure;

TimerService::TimerService()
{

    timerHandle = xTimerCreate(
        "AppTimer",
        pdMS_TO_TICKS(100),
        pdTRUE,
        this,
        &TimerService::timerCallbackStatic
    );
}

bool TimerService::setTimerImpl(uint16_t time, callbackFunc callback)
{
    this->callback = callback;


    xTimerChangePeriod(timerHandle, pdMS_TO_TICKS(time), 0);


    xTimerStart(timerHandle, 0);

    return true;
}

bool TimerService::stopTimerImpl(uint16_t timeout)
{

    xTimerStop(timerHandle, timeout);

    return true;
}




void TimerService::timerCallback()
{
    if (callback) {
        callback();
    }
}

