/**
 * ESP/Arduino Core Library
 * Copyright 2025 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "Task.h"

F_USE_NAMESPACE

void Task::suspendAll()
{
    vTaskSuspendAll();
}

void Task::resumeAll()
{
    xTaskResumeAll();
}

void Task::delay(uint32_t milliseconds)
{
    vTaskDelay(milliseconds / portTICK_PERIOD_MS);
}

uint32_t Task::totalTaskCount()
{
    return uxTaskGetNumberOfTasks();
}

TaskHandle_t Task::getCurrentTaskHandle()
{
    return xTaskGetCurrentTaskHandle();
}

Task::core_t Task::getTaskCore(TaskHandle_t taskHandle)
{
    BaseType_t core = xTaskGetAffinity(taskHandle);
    return core < 0 || core > 1 ? CORE_ANY : static_cast<core_t>(core);
}

const char* Task::getTaskName(TaskHandle_t taskHandle)
{
    return pcTaskGetTaskName(taskHandle);
}

void Task::printCurrentTaskInfo()
{
    TaskHandle_t currentTask = getCurrentTaskHandle();
    Serial.printf("Current Task: %s, Core: %d, Priority: %d\n",
                  getTaskName(currentTask),
                  getTaskCore(currentTask),
                  uxTaskPriorityGet(currentTask));
}

Task::Task(const char* pName, core_t core, uint32_t priority, uint32_t stackSize)
{
    BaseType_t affinity = core < 0 || core > 1 ? tskNO_AFFINITY : core;

    BaseType_t result = xTaskCreatePinnedToCore(
        &Task::_taskEntry,
        pName,
        stackSize / 4,
        this,
        priority,
        &_taskHandle,
        affinity
    );

    if (result != pdPASS) {
        // handle error
    }
}

Task::~Task()
{
    vTaskDelete(_taskHandle);
    _taskHandle = nullptr;
}

void Task::delayUntil(uint32_t time)
{
    vTaskDelayUntil(&_taskStartTicks, time / portTICK_PERIOD_MS);
}

void Task::_taskEntry(void* pParam)
{
    Task* pTask = static_cast<Task*>(pParam);
    pTask->_taskStartTicks = xTaskGetTickCount();
    pTask->run();
}