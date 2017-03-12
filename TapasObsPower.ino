#include <NCD4Relay.h>
#include <neopixel.h>

NCD4Relay relayController;
Adafruit_NeoPixel neoPixels(83, D5, WS2812B);

SYSTEM_MODE(AUTOMATIC);

int triggerRelay(String command);

int Dome = 1;
int MM200 = 2;
int Scopes = 3;
int Weather = 4;

/* This function is called once at start up ----------------------------------*/
void setup()
{
    Particle.function("ObsPower", triggerRelay);
    Particle.function("ObsLight", light);
    relayController.setAddress(0,0,0);
    RGB.control(true);
    RGB.brightness(0);
    pinMode(D5, OUTPUT);
    neoPixels.begin();
}

/* This function loops forever --------------------------------------------*/
void loop()
{
}

int light(String command) {
    int r = command.substring(0,command.indexOf(':')).toInt();
    command = command.substring(command.indexOf(':')+1);
    int g = command.substring(0,command.indexOf(':')).toInt();
    command = command.substring(command.indexOf(':')+1);
    int b = command.substring(0,command.indexOf(':')).toInt();
    command = command.substring(command.indexOf(':')+1);
    int brightness = command.substring(0,command.indexOf(':')).toInt();

    uint16_t i;

    for(i=0; i<neoPixels.numPixels(); i++) {
        neoPixels.setPixelColor(i, neoPixels.Color(r, g, b));
    }
    neoPixels.setBrightness(brightness);
    neoPixels.show();
}

int triggerRelay(String fullCommand){
    
    String equipment = fullCommand.substring(0,fullCommand.indexOf(':'));
    String command = fullCommand.substring(fullCommand.indexOf(':')+1);

    if(equipment.equalsIgnoreCase("All")) {
        triggerRelay("Dome:"+command);
        triggerRelay("MM200:"+command);
        triggerRelay("Scopes:"+command);
        triggerRelay("Weather:"+command);
        return 1;
    }

    //Relay Specific Command
    int relayNumber;
    String equip;

    if(equipment.equalsIgnoreCase("Dome")) {
        relayNumber = Dome;
        equip = "Dome";
    } else if(equipment.equalsIgnoreCase("MM200")) {
        relayNumber = MM200;
        equip = "MM200";
    } else if(equipment.equalsIgnoreCase("Scopes")) {
        relayNumber = Scopes;
        equip = "Scopes";
    } else if(equipment.equalsIgnoreCase("Weather")) {
        relayNumber = Weather;
        equip = "Weather";
    }
        
    if(command.equalsIgnoreCase("On")){
        relayController.turnOnRelay(relayNumber);
        Particle.publish(equip, "On", 16777215);
        return 1;
    }
    if(command.equalsIgnoreCase("Off")){
        relayController.turnOffRelay(relayNumber);
        Particle.publish(equip, "Off", 16777215);
        return 1;
    }
    return 0;
}
