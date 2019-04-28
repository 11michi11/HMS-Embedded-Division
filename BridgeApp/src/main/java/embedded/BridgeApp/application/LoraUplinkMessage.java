package embedded.BridgeApp.application;

import com.google.gson.annotations.SerializedName;

public class LoraUplinkMessage {
    @SerializedName("cmd")
    static final String MESSAGE_TYPE = "rx";
    @SerializedName("EUI")
    String eui;
    @SerializedName("ts")
    long timeInMilis;
    static final boolean ack = false;
    @SerializedName("fcnt")
    static int frameCounter;
    @SerializedName("port")
    static final int PORT = 5555;
    String data;

    public LoraUplinkMessage(String eui, String data) {
        this.eui = eui;
        timeInMilis = System.currentTimeMillis();
        frameCounter++;
        this.data = data;
    }

    public static void resetFrameCounter() {
        frameCounter = 0;
    }

}
