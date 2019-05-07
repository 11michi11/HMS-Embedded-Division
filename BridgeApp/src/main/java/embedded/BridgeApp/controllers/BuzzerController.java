package embedded.BridgeApp.controllers;

import embedded.BridgeApp.application.BuzzerControl;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

@RestController
@RequestMapping(path = "/buzzer")
public class BuzzerController {

    @Autowired
    private BuzzerControl controller;
    Logger logger = LoggerFactory.getLogger(BuzzerController.class);

    @PutMapping(path = "/{deviceID}")
    public void turnOnBuzzer(@PathVariable String deviceID) {
        logger.info("Turn on buzzer on device: " + deviceID);
        controller.turnOnBuzzer(deviceID);
    }

    @DeleteMapping(path = "/{deviceID}")
    public void turnOffBuzzer(@PathVariable String deviceID) {
        logger.info("Turn off buzzer on device: " + deviceID);
        controller.turnOffBuzzer(deviceID);
    }

}