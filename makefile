CC = gcc
DEBUG_CFLAGS = -Og -fsanitize=address -static-libasan -ggdb
CFLAGS = -Og -Wall -Wextra -Wno-unused-variable -Wno-misleading-indentation -Wno-unused-result -I./cJSON/ 
 


LIBS = -Iraylib/include raylib/lib/libraylib.a -lGL -lm -lpthread -ldl -lrt -lX11 

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

$(BUILD_FOLDER)/%.o: %.c | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

$(BUILD_FOLDER)/Map.o: Map/Map.c | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP 

$(BUILD_FOLDER)/cJSON.o: cJSON/cJSON.c | $(BUILD_FOLDER)
	$(CC) $(CFLAGS) -c $< -o $@ -MMD -MP

mem: $(TARGETA)

$(TARGETA): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LIBS) $(DEBUG_CFLAGS)

clean:
	rm -rf $(BUILD_FOLDER)
	rm -f $(TARGET)
	rm -f $(TARGETA)

# Refacrtor maybe
#SHADERS 300 OR 100 OR somthing webgl compatible
emcc:
	emcc -Os -std=c99 -s ASYNCIFY -s ALLOW_MEMORY_GROWTH=1 -s USE_GLFW=3 -s USE_WEBGL2=1 -s FULL_ES3=1 \
	--preload-file assets@assets --preload-file entJSON.json --preload-file nonEntJSON.json --preload-file genJSON.json --preload-file spriteJSON.json \
	--preload-file shaders@shaders --use-preload-plugins \
	ecs.c system.c renderer.c Map/Map.c items.c main.c cJSON/cJSON.c  -Iraylib/include raylib/lib/libraylib_wasm.a\
	 -o Web/index.html

serve:
	emrun --no_browser --port 8080 Web/index.html

cleanemcc:
	rm -f Web/index.html Web/index.js Web/index.wasm Web/index.data