#include "sensor_manager.h"
#include <stdio.h>
int main(void)
{
    SensorManager *m1 = SensorManager_GetInstance();
    SensorManager *m2 = SensorManager_GetInstance();

    if (m1 == m2)
        printf("Singleton verified: only ONE instance exists\n");

    SensorManager_Init("MainManager", NODE_TEMP, REAL_TIME, CONNECTED_DATABASE);
    SensorManager_PrintInfo();

    SensorManager_Init("SecondManager", NODE_LIGHT, PERIODIC, DISCONNECTED_DATABASE);
    SensorManager_PrintInfo();

    return 0;
}

