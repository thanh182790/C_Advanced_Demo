#ifndef LEGACY_UART_H
#define LEGACY_UART_H

#include <stdint.h>

/* Legacy driver cũ:
 * - Tên hàm không chuẩn
 * - API cứng, không theo interface mới
 */

void legacy_uart_init(uint32_t baud);
void legacy_uart_send_bytes(uint8_t *data, uint32_t len);
uint32_t legacy_uart_receive(uint8_t *buf, uint32_t max_len);

#endif

