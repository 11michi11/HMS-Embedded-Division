package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.data.HumidityData;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface HumidityRepository extends MongoRepository<HumidityData, String> {
}
