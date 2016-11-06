/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package thermostatPi;

import java.net.URL;
import java.util.ResourceBundle;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Button;
import javafx.scene.layout.Pane;

/**
 * FXML Controller class
 *
 * @author Marco
 */
public class SettingsController implements Initializable {

    public Main application;
    @FXML
    private Button exitLable;
    @FXML
    private Button goBackButton;
    @FXML
    private Pane settings;
       
    public void setApp(Main application){
        this.application = application;
    }
    
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        // TODO
    }    

    @FXML
    private void exit(ActionEvent event) {
        if (application == null){
            // We are running in isolated FXML, possibly in Scene Builder.
            // NO-OP.
            return;
        }
        
        application.userLogout();
    }

    @FXML
    private void goToProfile(ActionEvent event) {
        if (application == null){
            // We are running in isolated FXML, possibly in Scene Builder.
            // NO-OP.
            return;
        }
        
        application.gotoProfile();
    }
    
}
