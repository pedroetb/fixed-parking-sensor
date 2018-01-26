const int trigger1Pin = 2;
const int echo1Pin = 3;
const int trigger2Pin = 4;
const int echo2Pin = 5;
const int trigger3Pin = 6;
const int echo3Pin = 7;
const int buzzerPin = 9;

const unsigned long echoTimeout = 250000;

const int longDistanceThreshold = 350;
const int mediumDistanceThreshold = 200;
const int shortDistanceThreshold = 15;

const int highFrequency = 1000;
const int mediumFrequency = 600;
const int lowFrequency = 400;

const int toneDurationBasis = 200;
const int toneLongDistanceDelay = 6 * toneDurationBasis;
const int toneMediumDistanceDurationFactor = 3;
const int toneShortDistanceDuration = 2 * toneDurationBasis;

void setup() {

	pinMode(trigger1Pin, OUTPUT);
	pinMode(echo1Pin, INPUT);
	pinMode(trigger2Pin, OUTPUT);
	pinMode(echo2Pin, INPUT);
	pinMode(trigger3Pin, OUTPUT);
	pinMode(echo3Pin, INPUT);
	pinMode(buzzerPin, OUTPUT);
	//Serial.begin(115200);
}

void loop() {

	int d1 = getDistanceInCm(trigger1Pin, echo1Pin);
	int d2 = getDistanceInCm(trigger2Pin, echo2Pin);
	int d3 = getDistanceInCm(trigger3Pin, echo3Pin);

	int minDistance = min(min(d1, d2), d3);
	//Serial.println(minDistance);

	emitAcousticSignals(minDistance);
}

int getDistanceInCm(int triggerPin, int echoPin) {

	digitalWrite(triggerPin, LOW);
	delayMicroseconds(2);
	digitalWrite(triggerPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(triggerPin, LOW);

	unsigned long echoDelay = pulseIn(echoPin, HIGH, echoTimeout);

	return echoDelay * 5 / 292;
}

void emitAcousticSignals(int distanceInCm) {

	if ((distanceInCm <= 0) || (distanceInCm >= longDistanceThreshold)) {
		delay(toneDurationBasis);
	} else if (distanceInCm < shortDistanceThreshold) {
		tone(buzzerPin, highFrequency, toneShortDistanceDuration);
		delay(toneDurationBasis);
	} else if (distanceInCm < mediumDistanceThreshold) {
		int toneDuration = toneMediumDistanceDurationFactor * distanceInCm;
		int toneDelay = 2 * toneDuration;

		delay(toneDelay);
		tone(buzzerPin, mediumFrequency, toneDuration);
		delay(toneDelay);
		tone(buzzerPin, mediumFrequency, toneDuration);
	} else if (distanceInCm < longDistanceThreshold) {
		delay(toneLongDistanceDelay);
		tone(buzzerPin, lowFrequency, toneDurationBasis);
		delay(toneLongDistanceDelay);
		tone(buzzerPin, lowFrequency, toneDurationBasis);
	}
}
