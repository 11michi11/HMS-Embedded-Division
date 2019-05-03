package embedded.BridgeApp.application;

import com.google.gson.Gson;
import embedded.BridgeApp.persistance.MongoRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.WebSocket;
import java.nio.ByteBuffer;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.CompletionStage;

@Component
public class LoraClient implements WebSocket.Listener {

    private final MongoRepository mongoRepository;

    private WebSocket webSocket;
    private Gson gson;

    public LoraClient(MongoRepository mongoRepository) {
        this.mongoRepository = mongoRepository;
        gson = new Gson();
    }

    public void startListening(String url) {
        HttpClient client = HttpClient.newHttpClient();
        CompletableFuture<WebSocket> ws = client.newWebSocketBuilder()
                .buildAsync(URI.create(url), this);
    }

    //onOpen()
    public void onOpen(WebSocket webSocket) {
        // This WebSocket will invoke onText, onBinary, onPing, onPong or onClose methods on the associated listener (i.e. receive methods) up to n more times
        webSocket.request(1);
        System.out.println("WebSocket Listener has been opened for requests.");
        this.webSocket = webSocket;

//
//        var msg = new LoraDownlinkMessage("tx", "0004A30B0021D2A1", 1, false, "Bon Jovi went out in a Blaze of Glory because they stood behind Chuck Norris when he lit a fart!");
//        var gson = new Gson();
//        sendText(gson.toJson(msg), false);
    }

    public CompletionStage<?> onBinary(WebSocket webSocket, ByteBuffer data, boolean last) {
        System.out.println("On binary");
        webSocket.request(1);
        return null;
    }

    //onError()
    public void onError​(WebSocket webSocket, Throwable error) {
        System.out.println("A " + error.getCause() + " exception was thrown.");
        System.out.println("Message: " + error.getLocalizedMessage());
        webSocket.abort();
    }

    //onClose()
    public CompletionStage<?> onClose(WebSocket webSocket, int statusCode, String reason) {
        System.out.println("WebSocket closed!");
        System.out.println("Status:" + statusCode + " Reason: " + reason);
        return null; //new CompletableFuture().completedFuture("onClose() completed.").thenAccept(System.out::println);
    }

    //onPing()
    public CompletionStage<?> onPing​(WebSocket webSocket, ByteBuffer message) {
        webSocket.request(1);
        System.out.println("Ping: Client ---> Server");
        System.out.println(message.asCharBuffer().toString());
        return null; // new CompletableFuture().completedFuture("Ping completed.").thenAccept(System.out::println);
    }

    //onPong()
    public CompletionStage<?> onPong​(WebSocket webSocket, ByteBuffer message) {
        webSocket.request(1);
        System.out.println("Pong: Client ---> Server");
        System.out.println(message.asCharBuffer().toString());
        return null; // new CompletableFuture().completedFuture("Pong completed.").thenAccept(System.out::println);
    }

    //onText()
    public CompletionStage<?> onText​(WebSocket webSocket, CharSequence data, boolean last) {
        webSocket.request(1);
        System.out.println(data);
        LoraDownlinkMessage message = gson.fromJson(data.toString(), LoraDownlinkMessage.class);
        if (message.getCmd().equals("rx")) {
            List<Element> elements = LoraTranslator.translateDataFromDevice(message.getData(), message.getEui());
            System.out.println("Translated");
            elements.forEach(element -> System.out.println(element.toString() + " class: " + element.getClass().getSimpleName()));
            mongoRepository.save(elements);
        }
        return null; // new CompletableFuture().completedFuture("onText() completed.").thenAccept(System.out::println);
    }

    CompletableFuture<WebSocket> sendText(CharSequence message, boolean last) {
        return webSocket.sendText(message, last);
    }
}

// {"cmd":"rx","seqno":71,"EUI":"0004A30B0021D2A1","ts":1556867187288,"fcnt":0,"port":33,"freq":867100000,"rssi":-106,"snr":10,"toa":56,"dr":"SF7 BW125 4/5","ack":false,"bat":255,"data":"d5111c203f0313"}
