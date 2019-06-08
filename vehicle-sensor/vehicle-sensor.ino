constexpr uint8_t ledPin = 13;

bool measurementEnabled = false;
bool debugEnabled = true;


void setup() {

	pinMode(ledPin, OUTPUT);
	digitalWrite(ledPin, LOW);

	distanceSetup();
	soundSetup();
	radioSetup();

	if (debugEnabled) {
		Serial.begin(9600);
	}
}

void loop() {

	if (measurementEnabled) {
		checkDistance();
	}

	readRadio();
}

void checkDistance() {

	uint16_t distance = getMinDistanceInCm();
	emitAcousticSignals(distance);
}
