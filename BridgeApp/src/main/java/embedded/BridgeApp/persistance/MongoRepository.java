package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.Element;
import embedded.BridgeApp.application.Visitor;
import embedded.BridgeApp.application.data.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.List;

@Component
public class MongoRepository implements Visitor {

    private TemperatureRepository temperatureRepository;
    private CarbonDioxideRepository carbonDioxideRepository;
    private HumidityRepository humidityRepository;
    private MovementRepository movementRepository;
    private SoundRepository soundRepository;
    private LightRepository lightRepository;

    Logger logger = LoggerFactory.getLogger(MongoRepository.class);

    @Autowired
    public MongoRepository(TemperatureRepository temperatureRepository, CarbonDioxideRepository carbonDioxideRepository, HumidityRepository humidityRepository, MovementRepository movementRepository, SoundRepository soundRepository, LightRepository lightRepository) {
        this.temperatureRepository = temperatureRepository;
        this.carbonDioxideRepository = carbonDioxideRepository;
        this.humidityRepository = humidityRepository;
        this.movementRepository = movementRepository;
        this.soundRepository = soundRepository;
        this.lightRepository = lightRepository;
    }

    public void save(List<Element> elements) {
        logger.info("Saving " + elements.size() + " elements");
        elements.forEach(element -> element.acceptVisitor(this));
    }

    @Override
    public void saveCarbonDioxide(CarbonDioxideData data) {
        logger.info("Saving carbon: " + data);
        carbonDioxideRepository.save(data);
    }

    @Override
    public void saveTemperature(TemperatureData data) {
        logger.info("Saving temperature: " + data);
        temperatureRepository.save(data);
    }

    @Override
    public void saveHumidity(HumidityData data) {
        logger.info("Saving humidity: " + data);
        humidityRepository.save(data);
    }

    @Override
    public void saveMovement(MovementData data) {
        logger.info("Saving movement: " + data);
        movementRepository.save(data);
    }

    @Override
    public void saveSound(SoundData data) {
        logger.info("Saving sound: " + data);
        soundRepository.save(data);
    }

    @Override
    public void saveLight(LightData data) {
        logger.info("Saving light: " + data);
        lightRepository.save(data);
    }

    public void wipeDB(){
        logger.info("Deleting all content of Mongo database!!!");
        movementRepository.deleteAll();
        lightRepository.deleteAll();
        soundRepository.deleteAll();
        humidityRepository.deleteAll();
        carbonDioxideRepository.deleteAll();
        temperatureRepository.deleteAll();
    }
}
