package embedded.BridgeApp;

import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping(path = "/notification/{deviceId}")
public class NotificationController {

    @PostMapping
    public void putNotification(@PathVariable String deviceId){
        System.out.println(deviceId);
    }



}
