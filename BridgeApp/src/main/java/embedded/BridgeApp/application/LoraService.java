package embedded.BridgeApp.application;

import org.springframework.stereotype.Component;

@Component
public class LoraService implements LightsControl, BuzzerControl {
    @Override
    public void turnOnBuzzer(int deviceID) {

    }

    @Override
    public void turnOffBuzzer(int deviceID) {

    }

    @Override
    public void turnOnMovementDetection(int deviceID) {

    }

    @Override
    public void turnOffMovementDetection(int deviceID) {

    }
}
