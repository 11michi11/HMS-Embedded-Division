package embedded.BridgeApp.application;

import lombok.Data;

@Data
public class LoraDownlinkMessage {
    private String cmd;
    private String eui;
    private int port;
    private boolean confirmed;
    private String data;
}
