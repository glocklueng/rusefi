CC=gcc
CFLAGS=-c -Wall -std=c99 -I. -I../firmware/controllers/algo -I../firmware/controllers/math -I../firmware/util -I../firmware/controllers/sensors
LDFLAGS=
SOURCES= main.c boards.c \
	test_engine_math.c \
	test_event_registry.c \
	test_sensors.c \
	test_find_index.c test_fuel_map.c test_idle_controller.c test_interpolation_3d.c test_signal_executor.c \
	../firmware/controllers/math/engine_math.c \
	../firmware/controllers/algo/event_registry.c \
	../firmware/controllers/algo/interpolation.c \
	../firmware/controllers/algo/fuel_map.c \
	../firmware/controllers/sensors/thermistors.c \
	../firmware/controllers/sensors/maf.c \
	../firmware/controllers/sensors/voltage.c \
	../firmware/controllers/algo/signal_executor.c \
	../firmware/controllers/algo/signal_executor_single_timer_algo.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=tests

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@


