#define WIFI_SSID // Add wifi name
#define WIFI_PASSWORD // Add wifi password

#define ID "standing_desk" // Add unique name for this sensor
#define INTERVAL 10 //seconds

#define ULTRASONIC_PIN_TRIG 4 // Which pin is HC-SR04's trig connected txo
#define ULTRASONIC_PIN_ECHO 5 // Which pin is HC-SR04's echo connected to

#define GC_PORT 443
#define GC_PROM_URL "prometheus-us-central1.grafana.net"
#define GC_PROM_PATH "/api/prom/push"
#define GC_PROM_USER // User ID
#define GC_PROM_PASS // Add API key