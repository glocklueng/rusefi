rm -rf .dep/
make
svn info > ../firmware_binary/version
cp config/features.h ../firmware_binary
cp build/rusefi.hex ../firmware_binary
