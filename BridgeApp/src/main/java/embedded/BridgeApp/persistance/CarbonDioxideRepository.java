package embedded.BridgeApp.persistance;

import embedded.BridgeApp.application.data.CarbonDioxideData;
import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;

@Repository
public interface CarbonDioxideRepository extends MongoRepository<CarbonDioxideData, String> {
}
