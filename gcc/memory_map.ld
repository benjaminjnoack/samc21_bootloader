/* Memory Spaces Definitions */
MEMORY
{
  /* 16 kB from 0x00000000 to 0x00004000 */
  boot_rom  (rx)    : ORIGIN = 0x00000000, LENGTH = 0x00004000
  /* 240 kB from 0x00004000 to 0x00040000 */
  app_rom   (rx)    : ORIGIN = 0x00004000, LENGTH = 0x0003C000
  ram       (rwx)   : ORIGIN = 0x20000000, LENGTH = 0x00008000
}

__boot_rom_start__  = ORIGIN(boot_rom);
__boot_rom_size__   = LENGTH(boot_rom);
__app_rom_start__  = ORIGIN(app_rom);
__app_rom_size__   = LENGTH(app_rom);
