package embedded.BridgeApp.controllers;

import embedded.BridgeApp.application.LightsControl;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(path = "/movement")
public class AutomaticLightsController {

    @Autowired
    private LightsControl controller;

    @PutMapping(path = "/{deviceID}")
    public void turnOnMovementDetection(@PathVariable String deviceID) {
        System.out.println("Turn on movement on device: "+deviceID);
        controller.turnOnMovementDetection(deviceID);
    }

    @DeleteMapping(path = "/{deviceID}")
    public void turnOffMovementDetection(@PathVariable String deviceID) {
        System.out.println("Turn off movement on device: "+deviceID);
        controller.turnOffMovementDetection(deviceID);
    }

}
