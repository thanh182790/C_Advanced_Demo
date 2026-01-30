#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#define EVENT_LIST(X)                      \
    X(TEMPERATURE, 1, "Temperature Event") \
    X(HUMIDITY, 2, "Humidity Event")       \
    X(LOG_MESSAGE, 100, "Log Message")     \
    X(UNKNOW, 0, "Unknow Event") 

typedef enum
{
#define GEN_ENUM(id, val, str) id = val,
    EVENT_LIST(GEN_ENUM)
#undef GEN_ENUM
} EventType;

const char *eventToString(EventType e)
{
    switch (e)
    {
#define GEN_CASE(id, val, str) \
    case id:                   \
        return str;
        EVENT_LIST(GEN_CASE)
#undef GEN_CASE
    default:
        return "Unknown Event";
    }
}

typedef enum
{
    STATE_IDLE,
    STATE_READ_TEMP,
    STATE_READ_HUM,
    STATE_LOGGING,
    STATE_ERROR
} SensorState;

const char *stateToString(SensorState s)
{
    switch (s)
    {
    case STATE_IDLE:
        return "IDLE";
    case STATE_READ_TEMP:
        return "READ_TEMP";
    case STATE_READ_HUM:
        return "READ_HUM";
    case STATE_LOGGING:
        return "LOGGING";
    case STATE_ERROR:
        return "ERROR";
    default:
        return "???";
    }
}

float last_temp = 0.0f;
uint8_t last_hum = 0;
uint16_t last_bat = 0;
char last_msg[32] = "";

void handleEvent(EventType event)
{
    printf("  → Event: [%s]\n", eventToString(event));

    switch (event)
    {
    case TEMPERATURE:
        last_temp = 20.0f + (rand() % 200) / 10.0f;
        printf("    Temp: %.1f°C\n", last_temp);
        break;
    case HUMIDITY:
        last_hum = 30 + (rand() % 60);
        last_bat = 3000 + (rand() % 1000);
        printf("    Hum: %d%%, Battery: %dmV\n", last_hum, last_bat);
        break;
    case LOG_MESSAGE:
        const char *msgs[] = {"All OK", "High temp!", "Low battery", "Sensor error!"};
        snprintf(last_msg, sizeof(last_msg), "%s", msgs[rand() % 4]);
        printf("    Log: \"%s\"\n", last_msg);
        break;
    case UNKNOW:
        break;
    }
}

void runStateMachine()
{
    srand(time(NULL));

    SensorState state = STATE_IDLE;
    int step = 0;

    while (step < 10)
    {
        step++;
        printf("\n[Step %2d] State: [%s]\n", step, stateToString(state));

        EventType next_event = UNKNOW;

        switch (state)
        {
        case STATE_IDLE:
            if (rand() % 4 == 0)
            {
                state = STATE_LOGGING;
            }
            else
            {
                state = (rand() % 2) ? STATE_READ_TEMP : STATE_READ_HUM;
            }
            break;

        case STATE_READ_TEMP:
            next_event = TEMPERATURE;
            state = STATE_IDLE;
            break;

        case STATE_READ_HUM:
            next_event = HUMIDITY;
            state = STATE_IDLE;
            break;

        case STATE_LOGGING:
            next_event = LOG_MESSAGE;
            state = (rand() % 10 < 2) ? STATE_ERROR : STATE_IDLE;
            break;

        case STATE_ERROR:
            printf("  [ERROR] Resetting...\n");
            state = STATE_IDLE;
            break;
        }

        if (next_event != UNKNOW)
        {
            handleEvent(next_event);
        }
    }
}

int main(void)
{
    printf("\t\t=== MY DEMO ===\n");
    runStateMachine();
    return 0;
}