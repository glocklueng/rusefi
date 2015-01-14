
UTIL_TEST_SRC = $(PROJECT_DIR)/util/crc.c \
	$(PROJECT_DIR)/util/data_buffer.c \
	$(PROJECT_DIR)/util/histogram.c

UTILSRC = $(UTIL_TEST_SRC)
	
UTILSRC_CPP = $(PROJECT_DIR)/util/cyclic_buffer.cpp \
	$(PROJECT_DIR)/console_util/datalogging.cpp \
	$(PROJECT_DIR)/util/listener_array.cpp \
	$(PROJECT_DIR)/util/cli_registry.cpp \
	$(PROJECT_DIR)/util/efilib.cpp \
	$(PROJECT_DIR)/util/efilib2.cpp \
	$(PROJECT_DIR)/util/LocalVersionHolder.cpp
