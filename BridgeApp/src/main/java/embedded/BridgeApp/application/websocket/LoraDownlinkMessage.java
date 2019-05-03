package embedded.BridgeApp.application.websocket;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class LoraDownlinkMessage {
    private String cmd;
    private String EUI;
    private int port;
    private boolean confirmed;
    private String data;
}
