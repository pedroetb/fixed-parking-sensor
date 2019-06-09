#include <RH_ASK.h>

constexpr uint8_t radioRxPin = 6;
constexpr uint8_t radioTxPin = 5;

constexpr uint16_t radioSpeed = 2000;
constexpr uint16_t writeRadioInterval = 200;

uint32_t lastWriteRadioMillis = 0;

RH_ASK driver(radioSpeed, radioRxPin, radioTxPin);


void radioSetup() {

	if (!driver.init()) {
		Serial.println("Radio error");
	} else {
		driver.setModeTx();
	}
}

void writeRadio(uint8_t *msg) {

	if ((millis() - lastWriteRadioMillis) < writeRadioInterval) {
		return;
	}

	lastWriteRadioMillis = millis();

	writeRadioMessages(msg);
}

void writeRadioMessages(uint8_t *msg) {

	if (debugEnabled) {
		Serial.print("sending: ");
		Serial.println(String((char *)msg));
	}

	driver.send(msg, strlen(msg));
	driver.waitPacketSent();

	if (debugEnabled) {
		Serial.println("sent");
	}
}
