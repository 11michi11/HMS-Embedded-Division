package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.data.TemperatureData;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface TemperatureRepository extends MongoRepository<TemperatureData, String> {
}
