package embedded.BridgeApp.application;

public enum OperationCode {

    TURN_ON_BUZZER((byte)1),
    TURN_OFF_BUZZER((byte)2),
    TURN_ON_AUTOMATIC_LIGHTS((byte)3),
    TURN_OFF_AUTOMATIC_LIGHTS((byte)4);


    private byte code;

    OperationCode(byte code) {
        this.code = code;
    }

    public byte getCode() {
        return code;
    }
}
