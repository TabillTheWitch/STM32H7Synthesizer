#pragma once
#include <stdint.h>
#include <cstddef>
#include "StaticQueue.hpp"
#include "ButtonEventId.hpp"
#include "CompositionRoot.hpp"

#ifdef __cplusplus
extern "C" {
#endif

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);

#ifdef __cplusplus
}
#endif
