package embedded.BridgeApp.controllers;

import embedded.BridgeApp.application.BuzzerControl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(path = "/buzzer")
public class BuzzerController {

    @Autowired
    private BuzzerControl controller;

    @PutMapping(path = "/{deviceID}")
    public void turnOnBuzzer(@PathVariable String deviceID) {
        System.out.println("Turn on buzzer on device: "+deviceID);
        controller.turnOnBuzzer(deviceID);
    }

    @DeleteMapping(path = "/{deviceID}")
    public void turnOffBuzzer(@PathVariable String deviceID) {
        System.out.println("Turn off buzzer on device: "+deviceID);
        controller.turnOffBuzzer(deviceID);
    }

}