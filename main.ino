/* Copyright 2022 Vasile Alexandru-Gabriel (vasilealexandru37@gmail.com) */
   /* DEEA Project: Distance sensor with acoustic and light warnings. */

/* Delay to see the effects. */
const int delayTime = 50;

/* Delay for next computation. */
const int delayComputation = 100;

/* Pins used for ultrasonic sensor. */
const int echoPin = D5; 
const int trigPin = D3;

/* Required distances and sounds
frequencies for warnings. */
const int mediumDistance = 50;
const int lowDistance = 25;
const int highSound = 1000;
const int mediumSound = 500;
const int lowSound = 250;

/* Time for sound to go and come back. */
const int timeSound = 2;

/* Speed of light (cm / microseconds). */
const double soundSpeed = 0.034;

/* Pins used for RGB diode. */
const int red = D6;
const int green = D7;
const int blue = D8;

/* Pin for buzzer. */
const int buzzer = D2;

/* Helper vars for later computation. */
long duration;
double distance;

void setup()
{
  /* Start the serial communication 
  with the computer at 115200 bits/s. */
  Serial.begin(115200);
  
  /* Set the mode of the pins used by the RGB LED as OUTPUT. */
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);

  /* Set the mode of the pin used by the buzzer as OUTPUT. */
  pinMode(buzzer, OUTPUT);

  /* The trigger pin (transmitter) must be set as OUTPUT. */
  pinMode(trigPin, OUTPUT); 

  /* The echo pin (receiver) must be set as INPUT. */
  pinMode(echoPin, INPUT); 
}

void loop()
{
  /* Set the trigPin LOW in order to prepare for the next reading. */
  digitalWrite(trigPin, LOW);

  /* Delay for 2 microseconds. */
  delayMicroseconds(timeSound);

  /* Generate an ultrasound for 10
  microseconds then turn off the transmitter. */
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  /* Reads the echoPin, returns the
  sound wave travel time in microseconds. */
  duration = pulseIn(echoPin, HIGH);

  /* Use formula d = v * t / 2. */
  distance = duration * soundSpeed / 2;

  /* Show the distance in serial monitor. */
  Serial.println(distance);

  if (distance < lowDistance) {
    /* Create the beeping effect. */
    tone(buzzer, highSound);
    /* Turn on red light. */
    digitalWrite(red, HIGH);
    /* Delay to see effect. */
    delay(delayTime);

    /* Turn of light. */
    digitalWrite(red, LOW);
    /* Turn off the buzzer. */
    noTone(buzzer);
    /* Delay to see effect. */
    delay(delayTime);
  } else if (distance < mediumDistance) {
    /* Turn on the beeping effect. */
    tone(buzzer, mediumSound);
    /* Turn on the green effect. */
    digitalWrite(green, HIGH);
    /* Delay to see effect. */
    delay(delayTime);

    /* Turn off the green light. */
    digitalWrite(green, LOW);
    /* Turn off the buzzer. */
    noTone(buzzer);
    /* Delay to see effect. */
    delay(delayTime);
  } else {
    /* Turn on the beeping effect. */
    tone(buzzer, lowSound);
    /* Turn on the green effect. */
    digitalWrite(blue, HIGH);
    /* Delay to see effect. */
    delay(delayTime);

    /* Turn off the green light. */
    digitalWrite(blue, LOW);
    /* Turn off the buzzer. */
    noTone(buzzer);
    /* Delay to see effect. */
    delay(delayTime);
  }

  /* Wait for 0.1s. */
  delay(delayComputation);
}