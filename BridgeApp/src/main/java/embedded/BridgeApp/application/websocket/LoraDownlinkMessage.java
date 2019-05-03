package embedded.BridgeApp.application;

import lombok.AllArgsConstructor;
import lombok.Data;

@Data
@AllArgsConstructor
public class LoraDownlinkMessage {
    private String cmd;
    private String eui;
    private int port;
    private boolean confirmed;
    private String data;
}
