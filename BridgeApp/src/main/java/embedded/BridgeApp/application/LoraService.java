package embedded.BridgeApp.application;

import com.google.gson.Gson;
import embedded.BridgeApp.application.websocket.*;
import embedded.BridgeApp.persistance.MongoRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class LoraService implements LightsControl, BuzzerControl {

    private final LoraClient loraClient;
    private final MongoRepository mongoRepository;
    Logger logger = LoggerFactory.getLogger(LoraService.class);
    private static final String URL = "wss://iotnet.teracom.dk/app?token=vnoRhwAAABFpb3RuZXQudGVyYWNvbS5ka2Xs786OhFFEFSVzlDZhVRQ=";

    public LoraService(LoraClient loraClient, MongoRepository mongoRepository) {
        this.loraClient = loraClient;
        this.mongoRepository = mongoRepository;
        loraClient.setLoraService(this);
    }

    public void start() {
        loraClient.startListening(URL);
    }

    public void handleMessage(LoraUplinkMessage message){
        if (message.getCmd().equals("rx")) {
            List<Element> elements = LoraTranslator.translateDataFromDevice(message.getData(), message.getEUI());
            logger.info("Translated data:");
            elements.forEach(element -> logger.info(element.toString() + " class: " + element.getClass().getSimpleName()));
            mongoRepository.save(elements);
        }
    }

    @Override
    public void turnOnBuzzer(String deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_ON_BUZZER, deviceID);
        loraClient.sendText(data);
    }

    @Override
    public void turnOffBuzzer(String deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_OFF_BUZZER, deviceID);
        loraClient.sendText(data);
    }

    @Override
    public void turnOnMovementDetection(String deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_ON_AUTOMATIC_LIGHTS, deviceID);
        loraClient.sendText(data);
    }

    @Override
    public void turnOffMovementDetection(String deviceID) {
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_OFF_AUTOMATIC_LIGHTS, deviceID);
        loraClient.sendText(data);
    }


    public void runSendingTask(){
        var gson = new Gson();
        new Thread(()->{
            while(true){
                var msg1 = new LoraDownlinkMessage("0004A30B0021D2A1", "48656c6c6f");
                var msg2 = new LoraDownlinkMessage("0004A30B00259F36", "48656c6c6f");
                loraClient.sendText(gson.toJson(msg1));
                loraClient.sendText(gson.toJson(msg2));
                logger.info("Downlink message has been sent to 0004A30B0021D2A1 and 0004A30B00259F36, content: Hello");
                try {
                    Thread.sleep(1000*60);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        }).start();
    }

}


