#include <pgmspace.h>

#define SECRET
#define ThingName ""

const char WiFi_SSID[] = "";
const char WiFi_Password[] = "";
const char AWS_IoT_Endpoint[] = "";
const int AWS_IoT_Endpoint_Port = 8883;

// Amazon Root CA 1
static const char Amazon_Root_CA[] PROGMEM = R"EOF(

)EOF";

// Device Certificate
static const char Device_Cert[] PROGMEM = R"KEY(

)KEY";

// Device Private Key
static const char Device_PrivateKey[] PROGMEM = R"KEY(

)KEY";
