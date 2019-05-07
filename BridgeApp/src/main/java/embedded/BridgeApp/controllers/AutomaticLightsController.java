package embedded.BridgeApp.controllers;

import embedded.BridgeApp.application.BuzzerControl;
import embedded.BridgeApp.application.LightsControl;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(path = "/movement")
public class AutomaticLightsController {

    @Autowired
    private LightsControl controller;
    Logger logger = LoggerFactory.getLogger(AutomaticLightsController.class);

    @PutMapping(path = "/{deviceID}")
    public void turnOnMovementDetection(@PathVariable String deviceID) {
        logger.info("Turn on movement on device: " + deviceID);
        controller.turnOnMovementDetection(deviceID);
    }

    @DeleteMapping(path = "/{deviceID}")
    public void turnOffMovementDetection(@PathVariable String deviceID) {
        logger.info("Turn off movement on device: " + deviceID);
        controller.turnOffMovementDetection(deviceID);
    }

}
