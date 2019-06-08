constexpr uint8_t trigger1Pin = 4;
constexpr uint8_t echo1Pin = 5;
constexpr uint8_t trigger2Pin = 6;
constexpr uint8_t echo2Pin = 7;
constexpr uint8_t trigger3Pin = 8;
constexpr uint8_t echo3Pin = 9;

constexpr uint32_t echoTimeout = 250000;
constexpr uint16_t measurementInterval = 100;

uint32_t lastMeasurementMillis = 0;
uint16_t currentDistance = 0;


void distanceSetup() {

	pinMode(trigger1Pin, OUTPUT);
	pinMode(echo1Pin, INPUT);
	pinMode(trigger2Pin, OUTPUT);
	pinMode(echo2Pin, INPUT);
	pinMode(trigger3Pin, OUTPUT);
	pinMode(echo3Pin, INPUT);
}

uint16_t getMinDistanceInCm() {

	if (millis() < (lastMeasurementMillis + measurementInterval)) {
		return currentDistance;
	}

	lastMeasurementMillis = millis();

	currentDistance = getUpdatedMinDistanceInCm();
	if (debugEnabled) {
		Serial.print("distance: ");
		Serial.println(currentDistance);
	}

	return currentDistance;
}

uint16_t getUpdatedMinDistanceInCm() {

	uint16_t d1 = getDistanceInCm(trigger1Pin, echo1Pin);
	uint16_t d2 = getDistanceInCm(trigger2Pin, echo2Pin);
	uint16_t d3 = getDistanceInCm(trigger3Pin, echo3Pin);

	return min(min(d1, d2), d3);
}

uint16_t getDistanceInCm(uint8_t triggerPin, uint8_t echoPin) {

	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);

	uint32_t echoDelay = pulseIn(echoPin, HIGH, echoTimeout);

	return echoDelay * 5 / 292;
}
