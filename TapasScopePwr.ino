#include "NCD4Relay/NCD4Relay.h"

NCD4Relay relayController;

SYSTEM_MODE(AUTOMATIC);

int triggerRelay(String command);

int FSQ106 = 1;
int SVQ100 = 2;
int USBHub = 3;
int None = 4;

/* This function is called once at start up ----------------------------------*/
void setup()
{
    Particle.function("ScopePower", triggerRelay);
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
        triggerRelay("FSQ106:"+command);
        triggerRelay("SVQ100:"+command);
        triggerRelay("USBHub:"+command);
        return 1;
    }

    //Relay Specific Command
    int relayNumber;
    String equip;

    if(equipment.equalsIgnoreCase("FSQ106")) {
        relayNumber = FSQ106;
        equip = "FSQ106";
    } else if(equipment.equalsIgnoreCase("SVQ100")) {
        relayNumber = SVQ100;
        equip = "SVQ100";
    } else if(equipment.equalsIgnoreCase("USBHub")) {
        relayNumber = USBHub;
        equip = "USBHub";
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
