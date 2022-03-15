#include <lcom/lcf.h>

#include <stdint.h>

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
  /* To be implemented by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
  /* To be implemented by the students  */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int (util_sys_inb)(int port, uint8_t *value) {
  /* To be implemented by the students */
  if(value == NULL) return 1;
  uint32_t aux = 0;
  if(sys_inb(port, &aux)) return 1;
  //printf("%s is not yet implemented!\n", __func__);

  return 0;
}
