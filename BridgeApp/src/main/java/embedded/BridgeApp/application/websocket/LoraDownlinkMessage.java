package embedded.BridgeApp.application.websocket;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class LoraDownlinkMessage {
    private String cmd;
    private String EUI;
    private int port;
    private String data;

    public LoraDownlinkMessage(String deviceID, String data) {
        cmd = "tx";
        EUI = deviceID;
        port = 23;
        this.data = data;
    }
}
