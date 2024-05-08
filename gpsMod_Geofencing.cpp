//Code for GPS Module and Geofencing:

#include <TinyGPS++.h>
#include <SoftwareSerial.h>
#include <math.h>

#define RX_PIN 4 // Arduino Pin connected to the TX of the GPS module
#define TX_PIN 3 // Arduino Pin connected to the RX of the GPS module
#define LED_PIN A0

TinyGPSPlus gps; // the TinyGPS++ object
SoftwareSerial gpsSerial(RX_PIN, TX_PIN); // the serial interface to the GPS module

#define PI 3.14159265358979323846
#define GEOFENCE_LAT 18.56450 // replace with your latitude
#define GEOFENCE_LON 73.77314 // replace with your longitude
#define GEOFENCE_RADIUS 50 // in meters

double deg2rad(double degrees)
{
    return degrees * (PI / 180.0);
}

double distance(double lat1, double lon1, double lat2, double lon2)
{
    double R = 6371000; // Earth's radius in meters
    double phi1 = deg2rad(lat1);
    double phi2 = deg2rad(lat2);
    double deltaPhi = deg2rad(lat2 - lat1);
    double deltaLambda = deg2rad(lon2 - lon1);
    double a = sin(deltaPhi / 2) * sin(deltaPhi / 2) +
               cos(phi1) * cos(phi2) *
                   sin(deltaLambda / 2) * sin(deltaLambda / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double d = R * c;
    return d;
}

void setup()
{
    Serial.begin(9600);
    gpsSerial.begin(9600); // Default baud of NEO-6M GPS module is 9600
    Serial.println(F("Speed Detection System"));
}

void loop()
{
    if (gpsSerial.available() > 0)
    {
        if (gps.encode(gpsSerial.read()))
        {
            //geofencing code
            double lat = gps.location.lat();
            double lon = gps.location.lng();
            if (distance(lat, lon, GEOFENCE_LAT, GEOFENCE_LON) > GEOFENCE_RADIUS)
            {
                Serial.print("OUTSIDE");
                digitalWrite(LED_PIN, HIGH);
                digitalWrite(LED_PIN, LOW);
            }
            else
            {
                Serial.print("INSIDE");
                digitalWrite(LED_PIN, LOW);
            }
            Serial.print(" Distance: ");
            Serial.println(distance(lat, lon, GEOFENCE_LAT, GEOFENCE_LON));
            if (gps.location.isValid())
            {
                Serial.print(F("- latitude: "));
                Serial.println(gps.location.lat());
                Serial.print(F("- longitude: "));
                Serial.println(gps.location.lng());
                Serial.print(F("- altitude: "));
                if (gps.altitude.isValid())
                    Serial.println(gps.altitude.meters());
                else
                    Serial.println(F("INVALID"));
            }
            else
            {
                Serial.println(F("- location: INVALID"));
            }
            Serial.print(F("- speed: "));
            if (gps.speed.isValid())
            {
                Serial.print(gps.speed.kmph());
                Serial.println(F(" km/h"));
            }
            else
            {
                Serial.println(F("INVALID"));
            }
            Serial.println();
        }
    }
    if (millis() > 5000 && gps.charsProcessed() < 10)
        Serial.println(F("No GPS data received: check wiring"));
}
