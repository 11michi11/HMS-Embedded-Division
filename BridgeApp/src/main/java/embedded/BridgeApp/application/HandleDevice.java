package embedded.BridgeApp.application;

import embedded.BridgeApp.persistance.MongoRepository;
import lombok.Getter;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.messaging.simp.stomp.StompCommand;
import org.springframework.messaging.simp.stomp.StompHeaders;
import org.springframework.messaging.simp.stomp.StompSession;
import org.springframework.messaging.simp.stomp.StompSessionHandlerAdapter;

import java.lang.reflect.Type;

public class HandleDevice extends StompSessionHandlerAdapter {

    @Getter
    private int deviceId;

    @Autowired
    private MongoRepository mongoRepository;
    private String downlinkTopic = "/topic/messages";
    private String uplinkTopic = "/app/chat";
    private StompSession session;

    /*
     *@param data Json as String with prepared payload for uplink msg
     */
    public void sendCommand(String data) {
        session.send(uplinkTopic, data);
    }

    @Override
    public void afterConnected(StompSession session, StompHeaders connectedHeaders) {
        this.session = session;
        session.subscribe(downlinkTopic, this);
        session.send(uplinkTopic, "Sample msg");
    }

    @Override
    public void handleFrame(StompHeaders headers, Object payload) {
        Message msg = (Message) payload;
       // System.out.println("Received : " + msg.getText() + " from : " + msg.getFrom());
    }

    @Override
    public Type getPayloadType(StompHeaders headers) {
        return Message.class;
    }

    @Override
    public void handleException(StompSession session, StompCommand command, StompHeaders headers, byte[] payload, Throwable exception) {
        System.out.println("Got an exception" + exception);
    }

}
