
TRIGGER_SRC = 

TRIGGER_DECODERS_SRC_CPP = \
	$(PROJECT_DIR)/controllers/trigger/trigger_bmw.cpp \
	$(PROJECT_DIR)/controllers/trigger/trigger_mazda.cpp \
	$(PROJECT_DIR)/controllers/trigger/trigger_chrysler.cpp \
	$(PROJECT_DIR)/controllers/trigger/trigger_structure.cpp \
	$(PROJECT_DIR)/controllers/trigger/trigger_decoder.cpp \
	$(PROJECT_DIR)/controllers/trigger/trigger_mitsubishi.cpp \
	$(PROJECT_DIR)/controllers/trigger/trigger_gm.cpp

TRIGGER_SRC_CPP = \
	$(PROJECT_DIR)/controllers/trigger/trigger_emulator_algo.cpp \
	$(PROJECT_DIR)/controllers/trigger/rpm_calculator.cpp \
	$(PROJECT_DIR)/controllers/trigger/trigger_central.cpp \
	$(PROJECT_DIR)/controllers/trigger/main_trigger_callback.cpp
