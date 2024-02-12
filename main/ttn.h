#pragma once

void ttn_register(void (*callback)(uint8_t message));
void ttn_send(uint8_t * data, uint8_t data_size, uint8_t port, bool confirmed);
void ttn_response(uint8_t * buffer, size_t len);
size_t ttn_response_len()
