constexpr uint8_t buzzerPin = 3;

constexpr uint16_t highFrequency = 1000;
constexpr uint16_t mediumFrequency = 600;
constexpr uint16_t lowFrequency = 400;

constexpr uint16_t longDistanceThreshold = 350;
constexpr uint16_t mediumDistanceThreshold = 200;
constexpr uint16_t shortDistanceThreshold = 15;

constexpr uint16_t toneDurationBasis = 500;
constexpr uint16_t toneShortDistanceDuration = 2 * toneDurationBasis;
constexpr uint8_t toneMediumDistanceDurationFactor = 3;
constexpr uint16_t toneLongDistanceDuration = 6 * toneDurationBasis;

uint32_t lastSoundMillis = 0;
uint16_t currentToneDelay = 0;


void soundSetup() {

	pinMode(buzzerPin, OUTPUT);
}

void emitAcousticSignals(uint16_t distanceInCm) {

	if (millis() < (lastSoundMillis + currentToneDelay)) {
		return;
	}

	lastSoundMillis = millis();

	evaluateDistanceToEmitTone(distanceInCm);
}

void evaluateDistanceToEmitTone(uint16_t distanceInCm) {

	if ((distanceInCm <= 0) || (distanceInCm >= longDistanceThreshold)) {
		stopAcousticSignals();
	} else if (distanceInCm < shortDistanceThreshold) {
		emitShortRangeTone();
	} else if (distanceInCm < mediumDistanceThreshold) {
		emitMediumRangeTone(distanceInCm);
	} else if (distanceInCm < longDistanceThreshold) {
		emitLongRangeTone();
	}
}

void stopAcousticSignals() {

	noTone(buzzerPin);
}

void emitShortRangeTone() {

	tone(buzzerPin, highFrequency, toneShortDistanceDuration);
	currentToneDelay = toneShortDistanceDuration - 10;
}

void emitMediumRangeTone(uint16_t distanceInCm) {

	uint16_t toneDuration = toneMediumDistanceDurationFactor * distanceInCm;
	tone(buzzerPin, mediumFrequency, toneDuration);
	currentToneDelay = 2 * toneDuration;
}

void emitLongRangeTone() {

	tone(buzzerPin, lowFrequency, toneDurationBasis);
	currentToneDelay = toneLongDistanceDuration;
}
