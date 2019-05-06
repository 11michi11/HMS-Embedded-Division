package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.Element;
import embedded.BridgeApp.application.data.*;
import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import java.time.LocalDateTime;
import java.util.LinkedList;
import java.util.List;
import java.util.Random;

import static org.junit.jupiter.api.Assertions.assertEquals;

@RunWith(SpringRunner.class)
@SpringBootTest
public class MongoVisitorTest {

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

    @Autowired
    private MongoRepository mongoRepository;


//    @Test
//    void testVisitor() {
//        //setup
//        LocalDateTime now = LocalDateTime.now().withNano(0);
//        String id = "testDevice";
//        TemperatureData dataT = new TemperatureData(now, 15.0, id);
//        CarbonDioxideData dataC = new CarbonDioxideData(now, 200.0, id);
//        HumidityData dataH = new HumidityData(now, 15.0, id);
//        SoundData dataS = new SoundData(now, 15.0, id);
//        LightData dataL = new LightData(now, 15.0, id);
//        MovementData dataM = new MovementData(now, 15.0, id);
//        List<Element> elements = List.of(dataC, dataH, dataL, dataM, dataS, dataT);
//
//        mongoRepository.save(elements);
//
//        TemperatureData badDataT = new TemperatureData(LocalDateTime.MIN, 0.0, "bad");
//        CarbonDioxideData badDataC = new CarbonDioxideData(LocalDateTime.MIN, 0.0, "bad");
//        HumidityData badDataH = new HumidityData(LocalDateTime.MIN, 0.0, "bad");
//        SoundData badDataS = new SoundData(LocalDateTime.MIN, 0.0, "bad");
//        LightData badDataL = new LightData(LocalDateTime.MIN, 0.0, "bad");
//        MovementData badDataM = new MovementData(LocalDateTime.MIN, 0.0, "bad");
//
//        assertEquals(dataT, temperatureRepository.findById(id).orElse(badDataT));
//        assertEquals(dataC, carbonDioxideRepository.findById(id).orElse(badDataC));
//        assertEquals(dataH, humidityRepository.findById(id).orElse(badDataH));
//        assertEquals(dataS, soundRepository.findById(id).orElse(badDataS));
//        assertEquals(dataL, lightRepository.findById(id).orElse(badDataL));
//        assertEquals(dataM, movementRepository.findById(id).orElse(badDataM));
//
//
//        //clean up
//        movementRepository.delete(dataM);
//        lightRepository.delete(dataL);
//        soundRepository.delete(dataS);
//        humidityRepository.delete(dataH);
//        carbonDioxideRepository.delete(dataC);
//        temperatureRepository.delete(dataT);
//    }
//


}
