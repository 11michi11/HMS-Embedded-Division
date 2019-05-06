package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.data.*;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit.jupiter.SpringExtension;

import java.time.LocalDateTime;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;


@SpringBootTest
@ExtendWith(SpringExtension.class)
public class MongoRepositoryTest {

    @Autowired
    private TemperatureRepository temperatureRepository;
    @Autowired
    private CarbonDioxideRepository carbonDioxideRepository;
    @Autowired
    private SoundRepository soundRepository;
    @Autowired
    private HumidityRepository humidityRepository;
    @Autowired
    private MovementRepository movementRepository;
    @Autowired
    private LightRepository lightRepository;

//    @Test
//    void testTemperature() {
//        LocalDateTime now = LocalDateTime.now().withNano(0);
//        String id = "testDevice";
//        TemperatureData data = new TemperatureData(now, 15.0, id);
//        TemperatureData badData = new TemperatureData(LocalDateTime.MIN, 0.0, "bad");
//
//        temperatureRepository.save(data);
//
//        assertEquals(data, temperatureRepository.findById(id).orElse(badData));
//        temperatureRepository.delete(data);
//        assertFalse(temperatureRepository.findById(id).isPresent());
//    }
//
//    @Test
//    void testCarbon() {
//        LocalDateTime now = LocalDateTime.now().withNano(0);
//        String id = "testDevice";
//        CarbonDioxideData data = new CarbonDioxideData(now, 200.0, id);
//        CarbonDioxideData badData = new CarbonDioxideData(LocalDateTime.MIN, 0.0, "bad");
//
//        carbonDioxideRepository.save(data);
//
//        assertEquals(data, carbonDioxideRepository.findById(id).orElse(badData));
//        carbonDioxideRepository.delete(data);
//        assertFalse(carbonDioxideRepository.findById(id).isPresent());
//    }
//    @Test
//    void testHumidity() {
//        LocalDateTime now = LocalDateTime.now().withNano(0);
//        String id = "testDevice";
//        HumidityData data = new HumidityData(now, 15.0, id);
//        HumidityData badData = new HumidityData(LocalDateTime.MIN, 0.0, "bad");
//
//        humidityRepository.save(data);
//
//        assertEquals(data, humidityRepository.findById(id).orElse(badData));
//        humidityRepository.delete(data);
//        assertFalse(humidityRepository.findById(id).isPresent());
//    }
//    @Test
//    void testSound() {
//        LocalDateTime now = LocalDateTime.now().withNano(0);
//        String id = "testDevice";
//        SoundData data = new SoundData(now, 15.0, id);
//        SoundData badData = new SoundData(LocalDateTime.MIN, 0.0, "bad");
//
//        soundRepository.save(data);
//
//        assertEquals(data, soundRepository.findById(id).orElse(badData));
//        soundRepository.delete(data);
//        assertFalse(soundRepository.findById(id).isPresent());
//    }
//    @Test
//    void testLight() {
//        LocalDateTime now = LocalDateTime.now().withNano(0);
//        String id = "testDevice";
//        LightData data = new LightData(now, 15.0, id);
//        LightData badData = new LightData(LocalDateTime.MIN, 0.0, "bad");
//
//        lightRepository.save(data);
//
//        assertEquals(data, lightRepository.findById(id).orElse(badData));
//        lightRepository.delete(data);
//        assertFalse(lightRepository.findById(id).isPresent());
//    }
//    @Test
//    void testMovement() {
//        LocalDateTime now = LocalDateTime.now().withNano(0);
//        String id = "testDevice";
//        MovementData data = new MovementData(now, 15.0, id);
//        MovementData badData = new MovementData(LocalDateTime.MIN, 0.0, "bad");
//
//        movementRepository.save(data);
//
//        assertEquals(data, movementRepository.findById(id).orElse(badData));
//        movementRepository.delete(data);
//        assertFalse(movementRepository.findById(id).isPresent());
//    }
}
