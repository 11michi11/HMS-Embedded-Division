package embedded.BridgeApp.application;

import com.google.gson.annotations.Expose;
import com.google.gson.annotations.SerializedName;

public class LoraUplinkMessage {
    @SerializedName("cmd")
    @Expose
    static final String MESSAGE_TYPE = "rx";

    @SerializedName("EUI")
    @Expose
    String eui;

    @SerializedName("ts")
    @Expose
    long timeInMilis;

    @Expose
    static final boolean ack = false;

    @Expose
    @SerializedName("fcnt")
    int frameCounter;

    @Expose
    @SerializedName("port")
    static final int PORT = 5555;

    @Expose
    String data;

    static int nextFrame = 0;

    public LoraUplinkMessage(String eui, String data) {
        this.eui = eui;
        timeInMilis = System.currentTimeMillis();
        frameCounter = nextFrame;
        nextFrame++;
        this.data = data;
    }

    public static void resetFrameCounter() {
        nextFrame = 0;
    }

}
