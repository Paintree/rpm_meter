all: build

TARGET = RPM_Meter
PROJECT_DIR = ${shell pwd}
BUILD_DIR = ${PROJECT_DIR}/build
AVR_TOOLS_PATH = /usr/bin/avrdude
PROGRAMMER = arduino
MCU = m328p
PORT = /dev/ttyUSB0
BAUD_RATE = 57600

BINARY = $(BUILD_DIR)/$(TARGET)
GREEN = \033[1;32m


.PHONY: build cmake all

all: build

cmake:
	cmake . -B${BUILD_DIR} -DBUILD_DIR:STRING=${BUILD_DIR}

build: cmake
	${MAKE} -C ${BUILD_DIR}
	@echo "${GREEN}Built successfully!"

clean:
	rm -rf ${BUILD_DIR}


flash:
	@echo "Uploading $(BINARY)..."
	@$(AVR_TOOLS_PATH) -c $(PROGRAMMER) -p $(MCU) -P $(PORT) -b $(BAUD_RATE) -U flash:w:$(BINARY):e
	

deps:
	apt update
	DEBIAN_FRONTEND=noninteractive apt install \
	avr-libc \
	avrdude \
	binutils-avr \
	gcc-avr