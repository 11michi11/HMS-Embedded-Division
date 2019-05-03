package embedded.BridgeApp.application;

import org.springframework.stereotype.Component;

@Component
public class LoraService implements LightsControl, BuzzerControl {

    private final LoraClient loraClient;

    private static final String URL = "wss://iotnet.teracom.dk/app?token=vnoRhwAAABFpb3RuZXQudGVyYWNvbS5ka2Xs786OhFFEFSVzlDZhVRQ=";
    private HandleDevice sessionHandler;

    public LoraService(LoraClient loraClient) {
        this.loraClient = loraClient;
    }

    public void start() {
        loraClient.startListening(URL);
    }

    @Override
    public void turnOnBuzzer(String deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_ON_BUZZER, deviceID);
        sessionHandler.sendCommand(data);
    }

    @Override
    public void turnOffBuzzer(String deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_OFF_BUZZER, deviceID);
        sessionHandler.sendCommand(data);
    }

    @Override
    public void turnOnMovementDetection(String deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_ON_AUTOMATIC_LIGHTS, deviceID);
        sessionHandler.sendCommand(data);
    }

    @Override
    public void turnOffMovementDetection(String deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_OFF_AUTOMATIC_LIGHTS, deviceID);
        sessionHandler.sendCommand(data);
    }
}


