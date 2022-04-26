 #pragma once
  
 #include <stdbool.h>
  
 #include <minix/syslib.h>
  
 #define PB2BASE(x) (((x) >> 4) & 0x0F000) // phys_bytes to segment base
 #define PB2OFF(x) ((x) & (0x0FFFF))       // phys_bytes to segment offset
  
 typedef struct {
   phys_bytes phys; 
   void *virt;      
   size_t size;     
 } mmap_t;
  
 void *lm_init(bool enable_logging);
  
 void *lm_alloc(size_t size, mmap_t *map);
  
 bool lm_free(const mmap_t *map);