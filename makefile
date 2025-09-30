CC = gcc
CFLAGS = -Og -Wall -Wextra -Wno-unused-variable -Wno-misleading-indentation -I./cJSON/ -static-libasan
DEBUG_CFLAGS = -Og -fsanitize=address -static-libasan

LIBS = -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 

SRCS = ecs.c system.c renderer.c Map/Map.c items.c main.c cJSON/cJSON.c 
DEPS = $(SRCS:.c=.d)

BUILD_FOLDER = Build

# Generate object files in the Build directory
OBJS = $(addprefix $(BUILD_FOLDER)/, $(patsubst %.c,%.o,$(notdir $(SRCS))))

TARGET = main
TARGETA = mainMem

.PHONY: all clean mem

all: $(TARGET)

-include $(OBJS:.o=.d)

$(BUILD_FOLDER):
	mkdir -p $(BUILD_FOLDER)

$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS)

# General compilation rule for all source files, including those in subdirectories
$(BUILD_FOLDER)/%.o: %.c | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

# Specific rule for Map/Map.c
$(BUILD_FOLDER)/Map.o: Map/Map.c | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

# Specific rule for cJSON/cJSON.c
$(BUILD_FOLDER)/cJSON.o: cJSON/cJSON.c | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

mem: $(TARGETA)

$(TARGETA): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS) $(DEBUG_CFLAGS)

clean:
	rm -rf $(BUILD_FOLDER)
	rm -f $(TARGET)
	rm -f $(TARGETA)