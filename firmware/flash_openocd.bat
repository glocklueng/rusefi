openocd-0.8.0.exe -f interface/stlink-v2.cfg -f board/stm32f4discovery.cfg -c "program rusefi.bin verify reset exit 0x08000000"
