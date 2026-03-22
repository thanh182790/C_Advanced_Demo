#ifndef SENSOR_MANAGER_H
#define SENSOR_MANAGER_H

#define SIZE_OF_NAME_SENSOR_MANAGER 20

#define DISCONNECTED_DATABASE 0
#define CONNECTED_DATABASE 1

typedef enum
{
    NODE_TEMP,
    NODE_HUMID,
    NODE_LIGHT,
} NodeManager;

typedef enum
{
    REAL_TIME,
    PERIODIC,
} DataCollectionMethod;

typedef struct
{
    NodeManager currentNode;
    DataCollectionMethod dataCollectionMethod;
    char nameSensorManager[SIZE_OF_NAME_SENSOR_MANAGER];
    int statusConnectDatabase;
} SensorManager;

/* Singleton API */
SensorManager *SensorManager_GetInstance(void);

/* Business API */
void SensorManager_Init(const char *name,
                        NodeManager node,
                        DataCollectionMethod method,
                        int db_status);

void SensorManager_PrintInfo(void);

#endif
