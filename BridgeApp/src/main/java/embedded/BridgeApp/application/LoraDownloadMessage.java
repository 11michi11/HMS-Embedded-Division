package embedded.BridgeApp.application;

public class LoraDownloadMessage {
    private String cmd;
    private String eui;
    private int port;
    private boolean confirmed;
    private String data;

    public LoraDownloadMessage(String cmd, String eui, int port, boolean confirmed, String data) {
        this.cmd = cmd;
        this.eui = eui;
        this.port = port;
        this.confirmed = confirmed;
        this.data = data;
    }
}
