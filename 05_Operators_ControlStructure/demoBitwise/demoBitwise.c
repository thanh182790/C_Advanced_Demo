#include <stdint.h>
#include <stdio.h>

#define BIT(n) (1U << (n))

void print_bin32(uint32_t v)
{
    for (int i = 31; i >= 0; i--) {
        printf("%d", (v >> i) & 1);
        if (i % 4 == 0) printf(" ");
    }
}

void log_reg(const char* action, uint32_t reg)
{
    printf("=== %s ===\n", action);
    printf("HEX: 0x%08X\n", reg);
    printf("BIN: "); 
    print_bin32(reg);
    printf("\n\n");
}

/*
 *  SYSTEM_REG = 0b00000000000000000000000110111001
 *  | --- | --------------- | ------------- |
 *  | 0   | Living room LED | 1 (ON)        |
 *  | 1   | Bedroom LED     | 0 (OFF)       |
 *  | 2   | Kitchen LED     | 0 (OFF)       |
 *  | 3   | Hallway LED     | 1 (ON)        |
 *  | 4   | Door sensor     | 1 (OPEN)      |
 *  | 5   | Motion sensor   | 1 (Detected)  |
 *  | 7   | Security alarm  | 1 (ON)        |
 *  | 8   | Air conditioner | 0 (OFF)       |
 *  | 9   | Heater          | 1 (ON)        |
 *  | 6   | Fire alarm      | 0 (OFF)       |
 * */
void smart_home_demo()
{
    // ===============================================
    //  INITIAL SYSTEM STATE
    // ===============================================
    uint32_t SYSTEM_REG = 
        BIT(0) |        // living room LED ON
        BIT(3) |        // hallway LED ON
        BIT(4) |        // door OPEN
        BIT(5) |        // motion detected
        BIT(7) |        // alarm ON
        BIT(9);         // heater ON

    log_reg("Initial SYSTEM_REG (Real system state)", SYSTEM_REG);

    // ==================================================
    // 1. Turn OFF hallway LED (bit 3)
    // ==================================================
    SYSTEM_REG &= ~BIT(3);
    log_reg("Turn OFF hallway LED (bit 3)", SYSTEM_REG);

    // ==================================================
    // 2. Toggle bedroom LED (bit 1)
    // ==================================================
    SYSTEM_REG ^= BIT(1);
    log_reg("Toggle bedroom LED (bit 1)", SYSTEM_REG);

    // ==================================================
    // 3. Door closes → clear bit 4
    // ==================================================
    SYSTEM_REG &= ~BIT(4);
    log_reg("Door CLOSED → clear bit 4", SYSTEM_REG);

    // Alarm should turn OFF (bit 7)
    SYSTEM_REG &= ~BIT(7);
    log_reg("Turn OFF alarm because door is closed", SYSTEM_REG);

    // ==================================================
    // 4. Motion disappears → clear bit 5
    // ==================================================
    SYSTEM_REG &= ~BIT(5);
    log_reg("No motion detected → clear bit 5", SYSTEM_REG);

    // ==================================================
    // 5. Toggle air conditioner (bit 8)
    // ==================================================
    SYSTEM_REG ^= BIT(8);
    log_reg("Toggle air conditioner (bit 8)", SYSTEM_REG);

    // ==================================================
    // 6. Check if fire alarm is active (bit 6)
    // ==================================================
    printf("Check fire alarm (bit 6): %s\n\n",
        (SYSTEM_REG & BIT(6)) ? "ACTIVE" : "INACTIVE");

    // ==================================================
    // 7. System enters night mode → turn ON bedroom and kitchen LEDs
    // ==================================================
    SYSTEM_REG |= BIT(1) | BIT(2);
    log_reg("Night mode: turn ON bedroom (1) + kitchen (2) LEDs", SYSTEM_REG);

    // ==================================================
    // 8. System maintenance: invert register (demo only)
    // ==================================================
    uint32_t inverted = ~SYSTEM_REG;
    log_reg("Maintenance check → inverted SYSTEM_REG", inverted);
}

int main(void)
{
    smart_home_demo();
    return 0;
}

