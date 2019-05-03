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


//    public void javaEEWebsocket() {
//        try {
//            // open websocket
//            final WebsocketClientEndpoint clientEndPoint = new WebsocketClientEndpoint(new URI(URL));
//            // add listener
//            clientEndPoint.addMessageHandler(message -> System.out.println("Message from websocket " + message));
//
//            // send message to websocket
////            clientEndPoint.sendMessage("{'event':'addChannel','channel':'ok_btccny_ticker'}");
//            // wait 5 seconds for messages from websocket
//            Thread.sleep(5000);
//        } catch (InterruptedException ex) {
//            System.err.println("InterruptedException exception: " + ex.getMessage());
//        } catch (URISyntaxException ex) {
//            System.err.println("URISyntaxException exception: " + ex.getMessage());
//        }
//    }
//
//    public void springWebsocket() {
//        WebSocketClient client = new StandardWebSocketClient();
//
//        WebSocketStompClient stompClient = new WebSocketStompClient(client);
//        stompClient.setMessageConverter(new MappingJackson2MessageConverter());
//
//        sessionHandler = new HandleDevice();
//        stompClient.connect(URL, sessionHandler);
//        System.out.println("Lora started");
//    }
}


