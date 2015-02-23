
cd ../firmware
echo Compiling
pwd
rm -rf .dep/

rm -rf build\rusefi.bin
make


cd build
arm-none-eabi-size  --format=berkeley "rusefi.elf"
echo Flashing
pwd
call ../flash_openocd
cd ..


cd ..
echo Running some commands
pwd

java -cp java_console_binary\rusefi_console.jar com.rusefi.CmdLine "set_led_blinking_period 10"
