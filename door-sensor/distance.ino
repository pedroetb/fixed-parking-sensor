constexpr uint8_t triggerPin = 3;
constexpr uint8_t echoPin = 4;

constexpr uint32_t echoTimeout = 250000;
constexpr uint16_t measurementInterval = 500;

uint32_t lastMeasurementMillis = 0;
uint16_t currentDistance = 0;


void distanceSetup() {

	pinMode(triggerPin, OUTPUT);
	pinMode(echoPin, INPUT);
}

uint16_t getCurrentDistanceInCm() {

	if (millis() < (lastMeasurementMillis + measurementInterval)) {
		return currentDistance;
	}

	lastMeasurementMillis = millis();

	currentDistance = getDistanceInCm(triggerPin, echoPin);
	if (debugEnabled) {
		Serial.print("distance: ");
		Serial.println(currentDistance);
	}

	return currentDistance;
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
