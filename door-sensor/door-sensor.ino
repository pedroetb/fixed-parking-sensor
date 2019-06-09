constexpr uint8_t ledPin = 13;
constexpr uint16_t distanceThreshold = 10;

bool debugEnabled = true;


void setup() {

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);

	distanceSetup();
	radioSetup();

	if (debugEnabled) {
		Serial.begin(9600);
	}
}

void loop() {

	uint16_t distance = getCurrentDistanceInCm();
	checkDistance(distance);
}

void checkDistance(uint16_t distance) {

	const char *msg;

	if (distance > distanceThreshold) {
		digitalWrite(ledPin, LOW);
		msg = "off";
	} else {
		digitalWrite(ledPin, HIGH);
		msg = "on";
	}

	writeRadio(msg);
}
