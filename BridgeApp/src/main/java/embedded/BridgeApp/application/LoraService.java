package embedded.BridgeApp.application;

import org.springframework.messaging.converter.MappingJackson2MessageConverter;
import org.springframework.messaging.simp.stomp.StompSessionHandler;
import org.springframework.stereotype.Component;
import org.springframework.web.socket.client.WebSocketClient;
import org.springframework.web.socket.client.standard.StandardWebSocketClient;
import org.springframework.web.socket.messaging.WebSocketStompClient;

import java.util.Scanner;

@Component
public class LoraService implements LightsControl, BuzzerControl {


    private static final String URL = "lora";
    private HandleDevice sessionHandler;

    public LoraService() {
        WebSocketClient client = new StandardWebSocketClient();

        WebSocketStompClient stompClient = new WebSocketStompClient(client);
        stompClient.setMessageConverter(new MappingJackson2MessageConverter());

        sessionHandler = new HandleDevice();
        stompClient.connect(URL, sessionHandler);

        new Scanner(System.in).nextLine(); // Don't close immediately.
    }

    @Override
    public void turnOnBuzzer(int deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_ON_BUZZER, deviceID);
        sessionHandler.sendCommand(data);
    }

    @Override
    public void turnOffBuzzer(int deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_OFF_BUZZER, deviceID);
        sessionHandler.sendCommand(data);
    }

    @Override
    public void turnOnMovementDetection(int deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_ON_AUTOMATIC_LIGHTS, deviceID);
        sessionHandler.sendCommand(data);
    }

    @Override
    public void turnOffMovementDetection(int deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_OFF_AUTOMATIC_LIGHTS, deviceID);
        sessionHandler.sendCommand(data);
    }
}
