#ifndef HEADER_H
#define HEADER_H

void motorSetup(void);
void serialSetup(void);
void wiFiSetup(void);
void otaSetup(void);
void serverSetup(void);
void adsSetup(void);

void handleMain(void);
void handleSensor(int pin);
void handleS1(void);
void handleS2(void);
void handleS3(void);
void handleS4(void);
void fetchSensorValue(int chan);
void fetchSensorValues(void);


#endif