package embedded.BridgeApp.application;

import org.springframework.stereotype.Component;

import java.util.LinkedList;
import java.util.List;

@Component
public class LoraService implements LightsControl, BuzzerControl {

    private List<HandleDevice> deviceHandlers;

    public LoraService() {
        deviceHandlers = new LinkedList<>();
    }

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
