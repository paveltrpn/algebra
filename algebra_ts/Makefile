
SOURCE_PREFIX = src
BUILD_PREFIX = build

SRCS = main.ts \
	   vec2.ts \
	   vec3.ts \
	   cmplx.ts 

TSC = tsc
CFLAGS = --strict --target "ES6" --module "ES6" --noImplicitAny --removeComments --preserveConstEnums

VPATH := $(SOURCE_PREFIX)

OBJS := $(patsubst %.ts,$(BUILD_PREFIX)/%.js,$(SRCS))

.PHONY: all clean

all: $(OBJS)

$(BUILD_PREFIX)/%.js: %.ts
	$(TSC) $(CFLAGS) $< --outDir $(BUILD_PREFIX)

clean:
	rm -f $(BUILD_PREFIX)/*.js