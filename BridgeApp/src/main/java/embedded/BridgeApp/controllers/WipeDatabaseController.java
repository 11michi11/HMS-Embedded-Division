package embedded.BridgeApp.controllers;

import embedded.BridgeApp.persistance.MongoRepository;
import org.springframework.web.bind.annotation.DeleteMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
public class WipeDatabaseController {

    private final MongoRepository mongoRepository;

    public WipeDatabaseController(MongoRepository mongoRepository) {
        this.mongoRepository = mongoRepository;
    }

    @DeleteMapping("/secret/deleteDB")
    public void deleteDatabase() {
        mongoRepository.wipeDB();
    }

}
