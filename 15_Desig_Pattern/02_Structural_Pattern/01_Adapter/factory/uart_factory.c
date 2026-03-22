#include "uart_factory.h"

#if defined(USE_NEW_UART)
#include "new_uart.h"
#endif

#if defined(USE_LEGACY_UART)
#include "legacy_uart_adapter.h"
#endif

UART_Interface UART_Factory_Create(UART_DriverType type)
{
#if defined(USE_NEW_UART)
    (void)type;   /* tránh warning */
    return NewUART_Create();

#elif defined(USE_LEGACY_UART)
    (void)type;
    return LegacyUART_Adapter_Create();

#else
#error "No UART driver selected"
#endif
}


