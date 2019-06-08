#include <RH_ASK.h>

constexpr uint8_t radioRxPin = 11;
constexpr uint8_t radioTxPin = 10;

constexpr uint16_t radioSpeed = 500;
constexpr uint16_t readRadioInterval = 5000;
constexpr uint16_t readRadioTimeout = 200;

uint32_t lastReadRadioMillis = 0;

RH_ASK driver(radioSpeed, radioRxPin, radioTxPin);


void radioSetup() {

	if (!driver.init()) {
		Serial.println("Radio error");
	} else {
		driver.setModeRx();
	}
}

void readRadio() {

	if ((millis() - lastReadRadioMillis) < readRadioInterval) {
		return;
	}

	lastReadRadioMillis = millis();

	readRadioMessages();
}

void readRadioMessages() {

	uint8_t buf[RH_ASK_MAX_MESSAGE_LEN];
	uint8_t buflen = sizeof(buf);

	driver.waitAvailableTimeout(readRadioTimeout);
	if (driver.recv(buf, &buflen)) {
		String msg = parseReceivedMessage(buf, buflen);
		evaluateMessage(msg);
	}
}

String parseReceivedMessage(uint8_t *buf, uint8_t buflen) {

	buf[buflen] = '\0';

	return String((char*)buf);
}

void evaluateMessage(String msg) {

	if (debugEnabled) {
		Serial.print("received: ");
		Serial.println(msg);
	}

	if ((msg == "on" && !measurementEnabled) || (msg == "off" && measurementEnabled)) {
		measurementEnabled = !measurementEnabled;
	}
}
