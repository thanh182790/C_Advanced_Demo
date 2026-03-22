#include "sensor_manager.h"
#include <stdio.h>
#include <string.h>

static SensorManager m_instance;
static int initialized = 0;

SensorManager* SensorManager_GetInstance(void)
{
    return &m_instance;
}

void SensorManager_Init(const char* name,
                         NodeManager node,
                         DataCollectionMethod method,
                         int db_status)
{
    if (initialized) {
        printf("SensorManager already initialized!\n");
        return;
    }

    snprintf(m_instance.nameSensorManager,
             sizeof(m_instance.nameSensorManager),
             "%s", name);

    m_instance.currentNode = node;
    m_instance.dataCollectionMethod = method;
    m_instance.statusConnectDatabase = db_status;

    initialized = 1;
}

static const char* getNodeManagerString(NodeManager node)
{
    switch (node) {
        case NODE_TEMP:  return "Temperature Node";
        case NODE_HUMID: return "Humidity Node";
        case NODE_LIGHT: return "Light Node";
        default:         return "Unknown Node";
    }
}

static const char* getDataCollectionMethodString(DataCollectionMethod method)
{
    switch (method) {
        case REAL_TIME: return "Real-time";
        case PERIODIC:  return "Periodic";
        default:        return "Unknown Method";
    }
}

void SensorManager_PrintInfo(void)
{
    if (!initialized) {
        printf("SensorManager not initialized\n");
        return;
    }

    printf("===== Sensor Manager Info =====\n");
    printf("Name   : %s\n", m_instance.nameSensorManager);
    printf("Node   : %s\n", getNodeManagerString(m_instance.currentNode));
    printf("Method : %s\n", getDataCollectionMethodString(m_instance.dataCollectionMethod));
    printf("DB     : %s\n",
           m_instance.statusConnectDatabase == CONNECTED_DATABASE ?
           "Connected" : "Disconnected");
    printf("================================\n");
}

