package embedded.BridgeApp;

import org.springframework.data.mongodb.repository.MongoRepository;

public interface MongoRepo extends MongoRepository<Test,String> {
}
