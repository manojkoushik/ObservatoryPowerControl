#include "NCD4Relay/NCD4Relay.h"

NCD4Relay relayController;

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
    relayController.setAddress(0,0,0);
    RGB.control(true);
    RGB.brightness(0);
}

/* This function loops forever --------------------------------------------*/
void loop()
{
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
