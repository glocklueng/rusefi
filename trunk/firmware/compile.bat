rm -rf .dep/
make
svn info > ../firmware_binary/version.txt
cp config/features.h ../firmware_binary
cp build/rusefi.hex ../firmware_binary

cd build
java -jar ../../java_tools/gcc_map_reader.jar > rusefi_ram_report.txt