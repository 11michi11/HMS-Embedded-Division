package embedded.BridgeApp.application;

public enum OperationCode {
    //turnOnBuzzer
    TURN_ON_BUZZER((byte)1);


    private byte code;

    OperationCode(byte code) {
        this.code = code;
    }
}
