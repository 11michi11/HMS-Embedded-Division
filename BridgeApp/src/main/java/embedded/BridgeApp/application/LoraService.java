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

    public LoraService() {
        WebSocketClient client = new StandardWebSocketClient();

        WebSocketStompClient stompClient = new WebSocketStompClient(client);
        stompClient.setMessageConverter(new MappingJackson2MessageConverter());

        StompSessionHandler sessionHandler = new HandleDevice();
        stompClient.connect(URL, sessionHandler);

        new Scanner(System.in).nextLine(); // Don't close immediately.
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
