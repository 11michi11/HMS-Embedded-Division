package embedded.BridgeApp.application;

import embedded.BridgeApp.application.data.Data;
import embedded.BridgeApp.application.websocket.LoraTranslator;
import embedded.BridgeApp.application.websocket.LoraUplinkMessage;
import embedded.BridgeApp.application.websocket.OperationCode;
import org.junit.jupiter.api.Test;

import java.util.List;

import static org.junit.jupiter.api.Assertions.assertEquals;

class LoraTranslatorTest {

    private String deviceId = "1234567890123456";

    @Test
    public void testTranslateDataFromDeviceOnlyLowCarbonByte() {

        // 80,0,58,92,0,30
        double[] values = {80,58,92,0,30};
        String data = "50003a5c001e";

        List<Element> list = LoraTranslator.translateDataFromDevice(data,deviceId);

        for (int i = 0; i<values.length;i++) {
            assertEquals(values[i],((Data) list.get(i)).getValue());
        }
        for (Element e: list) {
            assertEquals(deviceId,((Data) e).getDeviceId());
        }
    }

    @Test
    public void testTranslateDataFromDeviceBothBytesForCarbon() {

        // 21,3,58,92,10,30
        double[] values = {789,58,92,10,30};
        String data = "15033a5c0a1e";

        List<Element> list = LoraTranslator.translateDataFromDevice(data,deviceId);

        for (int i = 0; i<values.length;i++) {
            assertEquals(values[i],((Data) list.get(i)).getValue());
        }
        for (Element e: list) {
            assertEquals(deviceId,((Data) e).getDeviceId());
        }
    }

    @Test
    public void testTranslateOffLightOperation() {
        LoraUplinkMessage.resetFrameCounter();
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_OFF_AUTOMATIC_LIGHTS,deviceId);
        String time = data.substring(42,data.indexOf("ack")-2);
        String hexOpCode = "04";
        String expected = "{\"cmd\":\"rx\",\"EUI\":\"" + deviceId + "\",\"ts\":" + time +
                ",\"ack\":" + false + ",\"fcnt\":" + 0 + ",\"port\":" + 5555 + ",\"data\":\"" + hexOpCode + "\"}";
        assertEquals(expected,data);
    }

    @Test
    public void testTranslateOnLightOperation() {
        LoraUplinkMessage.resetFrameCounter();
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_ON_AUTOMATIC_LIGHTS,deviceId);
        String time = data.substring(42,data.indexOf("ack")-2);
        String hexOpCode = "03";
        String expected = "{\"cmd\":\"rx\",\"EUI\":\"" + deviceId + "\",\"ts\":" + time +
                ",\"ack\":" + false + ",\"fcnt\":" + 0 + ",\"port\":" + 5555 + ",\"data\":\"" + hexOpCode + "\"}";
        assertEquals(expected,data);
    }

    @Test
    public void testTranslateOnBuzzerOperation() {
        LoraUplinkMessage.resetFrameCounter();
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_ON_BUZZER,deviceId);
        String time = data.substring(42,data.indexOf("ack")-2);
        String hexOpCode = "01";
        String expected = "{\"cmd\":\"rx\",\"EUI\":\"" + deviceId + "\",\"ts\":" + time +
                ",\"ack\":" + false + ",\"fcnt\":" + 0 + ",\"port\":" + 5555 + ",\"data\":\"" + hexOpCode + "\"}";
        assertEquals(expected,data);
    }

    @Test
    public void testTranslateOffBuzzerOperation() {
        LoraUplinkMessage.resetFrameCounter();
        String data = LoraTranslator.translateOperationCodeToData(OperationCode.TURN_OFF_BUZZER,deviceId);
        String time = data.substring(42,data.indexOf("ack")-2);
        String hexOpCode = "02";
        String expected = "{\"cmd\":\"rx\",\"EUI\":\"" + deviceId + "\",\"ts\":" + time +
                ",\"ack\":" + false + ",\"fcnt\":" + 0 + ",\"port\":" + 5555 + ",\"data\":\"" + hexOpCode + "\"}";
        assertEquals(expected,data);
    }


}