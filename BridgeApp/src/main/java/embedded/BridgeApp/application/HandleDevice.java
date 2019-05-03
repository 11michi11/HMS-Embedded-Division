package embedded.BridgeApp.application;

import embedded.BridgeApp.persistance.MongoRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.stomp.StompCommand;
import org.springframework.messaging.simp.stomp.StompHeaders;
import org.springframework.messaging.simp.stomp.StompSession;
import org.springframework.messaging.simp.stomp.StompSessionHandlerAdapter;
import org.springframework.stereotype.Component;

import java.lang.reflect.Type;

@Component
public class HandleDevice extends StompSessionHandlerAdapter {

    @Autowired
    private MongoRepository mongoRepository;
    private String downlinkTopic = "/app?token=vnoRhwAAABFpb3RuZXQudGVyYWNvbS5ka2Xs786OhFFEFSVzlDZhVRQ=";
//    private String downlinkTopic = "/topic/greetings";
    private String uplinkTopic = "/app/hello";//"wss://iotnet.teracom.dk/app?token=vnoRhwAAABFpb3RuZXQudGVyYWNvbS5ka2Xs786OhFFEFSVzlDZhVRQ=";
    private StompSession session;

    /*
     *@param data Json as String with prepared payload for uplink msg
     */
    public void sendCommand(String data) {
        session.send(uplinkTopic, data);
    }

    @Override
    public void afterConnected(StompSession session, StompHeaders connectedHeaders) {
        System.out.println("Trying to subscribe");
        this.session = session;
        session.subscribe(downlinkTopic, this);
        System.out.println("Subscribed");
        session.send(uplinkTopic, "Sample msg");
    }

    @Override
    public void handleFrame(StompHeaders headers, Object payload) {
        System.out.println(payload);
        var msg = (LoraDownlinkMessage) payload;
//        List<Element> elements = LoraTranslator.translateDataFromDevice(msg.getData(), msg.getEui());
//        mongoRepository.save(elements);
        System.out.println("Received : " + msg.getData() + " from : " + msg.getEui());
    }

    @Override
    public Type getPayloadType(StompHeaders headers) {
        return LoraDownlinkMessage.class;
    }

    @Override
    public void handleException(StompSession session, StompCommand command, StompHeaders headers, byte[] payload, Throwable exception) {
        System.out.println("Got an exception" + exception);
    }

    @Override
    public void handleTransportError(StompSession session, Throwable exception) {
        System.out.println("Got an transport exception " + exception);
    }

}
