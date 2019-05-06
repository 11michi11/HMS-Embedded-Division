package embedded.BridgeApp.application.websocket;

import com.google.gson.Gson;
import embedded.BridgeApp.application.Element;
import embedded.BridgeApp.persistance.MongoRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.WebSocket;
import java.nio.ByteBuffer;
import java.util.Arrays;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionStage;

@Component
public class LoraClient implements WebSocket.Listener {

    private final MongoRepository mongoRepository;
    Logger logger = LoggerFactory.getLogger(LoraClient.class);
    private WebSocket webSocket;
    private Gson gson;

    public LoraClient(MongoRepository mongoRepository) {
        this.mongoRepository = mongoRepository;
        gson = new Gson();
    }

    public CompletionStage<?> onText​(WebSocket webSocket, CharSequence data, boolean last) {
        webSocket.request(1);
        LoraUplinkMessage message = gson.fromJson(data.toString(), LoraUplinkMessage.class);
        logger.info("Received text from " + message.getEUI() + ", with content: " + message.getData());
        if (message.getCmd().equals("rx")) {
            List<Element> elements = LoraTranslator.translateDataFromDevice(message.getData(), message.getEUI());
            logger.info("Translated data:");
            elements.forEach(element -> logger.info(element.toString() + " class: " + element.getClass().getSimpleName()));
            mongoRepository.save(elements);
        }
        return null; // new CompletableFuture().completedFuture("onText() completed.").thenAccept(System.out::println);
    }

    public void startListening(String url) {
        HttpClient client = HttpClient.newHttpClient();
        CompletableFuture<WebSocket> ws = client.newWebSocketBuilder()
                .buildAsync(URI.create(url), this);
    }

    public void onOpen(WebSocket webSocket) {
        // This WebSocket will invoke onText, onBinary, onPing, onPong or onClose methods on the associated listener (i.e. receive methods) up to n more times
        webSocket.request(1);
        logger.info("WebSocket Listener has been opened for requests.");
        this.webSocket = webSocket;

//
//        var msg = new LoraUplinkMessage("tx", "0004A30B0021D2A1", 1, false, "Bon Jovi went out in a Blaze of Glory because they stood behind Chuck Norris when he lit a fart!");
//        var gson = new Gson();
//        sendText(gson.toJson(msg), false);
    }

    public CompletionStage<?> onBinary(WebSocket webSocket, ByteBuffer data, boolean last) {
        logger.info("Received binary message " + Arrays.toString(data.array()));
        webSocket.request(1);
        return null;
    }

    public void onError​(WebSocket webSocket, Throwable error) {
        logger.error("A " + error.getCause() + " exception was thrown.", error);
        webSocket.abort();
    }

    public CompletionStage<?> onClose(WebSocket webSocket, int statusCode, String reason) {
        logger.info("WebSocket closed! Status:" + statusCode + " Reason: " + reason);
        return null; //new CompletableFuture().completedFuture("onClose() completed.").thenAccept(System.out::println);
    }

    public CompletionStage<?> onPing​(WebSocket webSocket, ByteBuffer message) {
        webSocket.request(1);
        logger.info("Ping: Client ---> Server " + message.asCharBuffer().toString());
        return null; // new CompletableFuture().completedFuture("Ping completed.").thenAccept(System.out::println);
    }

    public CompletionStage<?> onPong​(WebSocket webSocket, ByteBuffer message) {
        webSocket.request(1);
        logger.info("Pong: Client ---> Server " + message.asCharBuffer().toString());
        return null; // new CompletableFuture().completedFuture("Pong completed.").thenAccept(System.out::println);
    }

    public CompletableFuture<WebSocket> sendText(CharSequence message, boolean last) {
        logger.info("Sending text: " + message);
        return webSocket.sendText(message, last);
    }
}
// json from lorawan example
// {"cmd":"rx","seqno":71,"EUI":"0004A30B0021D2A1","ts":1556867187288,"fcnt":0,"port":33,"freq":867100000,"rssi":-106,"snr":10,"toa":56,"dr":"SF7 BW125 4/5","ack":false,"bat":255,"data":"d5111c203f0313"}
