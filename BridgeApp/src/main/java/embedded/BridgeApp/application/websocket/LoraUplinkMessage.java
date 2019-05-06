package embedded.BridgeApp.application.websocket;

import com.google.gson.annotations.SerializedName;
import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class LoraUplinkMessage {

    private String cmd;
    private String EUI;
    @SerializedName("ts")
    private long timeInMillis;
    @SerializedName("ack")
    private boolean acknowledgement;
    @SerializedName("fcnt")
    private int frameCounter;
    private int port;
    private String data;
}
