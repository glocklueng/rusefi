
cd ../firmware
echo Compiling
pwd
call compile.bat
pwd

cd ..

echo Running some commands
pwd

rem java -cp java_console_binary\rusefi_console.jar com.rusefi.CmdLine "set_led_blinking_period 10"

cd java_console

echo Running tests
ant realtest

IF NOT ERRORLEVEL echo ERROR DETECTED
IF NOT ERRORLEVEL 0 EXIT /B 1

