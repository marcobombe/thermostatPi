/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package thermostatPi;

import java.awt.Color;
import java.net.URL;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.ResourceBundle;
import javafx.application.Platform;
import javafx.beans.property.SimpleStringProperty;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.ProgressBar;
import javafx.scene.control.ProgressIndicator;
import javafx.scene.paint.Paint;
import javafx.scene.shape.Circle;

/**
 * FXML Controller class
 *
 * @author Marco
 */
public class statusPanel implements Initializable {

    DateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd");
    DateFormat timeFormat = new SimpleDateFormat("HH:mm:ss");
    Date date = new Date();
    Calendar cal = Calendar.getInstance();
    SimpleStringProperty dynamicTimeProperty = new SimpleStringProperty();
    SimpleStringProperty dynamicDateProperty = new SimpleStringProperty();
    
    double progress;
    
    public Main application;
       
    @FXML
    private ProgressBar progressBar;
    @FXML
    private Label dateLable;
    @FXML
    private Label timeLable;
    @FXML
    private Circle statusDot;

    /**
     * Initializes the controller class.
     * @param url
     * @param rb
     */
    @Override
    public void initialize(URL url, ResourceBundle rb) {
        
        progress=0.0;
        
        timeLable.setText(timeFormat.format(date));        
        dateLable.setText(dateFormat.format(cal.getTime()));
        
        timeLable.textProperty().bind(dynamicTimeProperty);
        dateLable.textProperty().bind(dynamicDateProperty);
        Thread t = new Thread(new Runnable() {
            @Override
            public void run() {
                    while (true) {
                            final SimpleDateFormat timeSdf = new SimpleDateFormat("HH:mm:ss");
                            final SimpleDateFormat dateSdf = new SimpleDateFormat("YYYY/MM/d");
                            Platform.runLater(new Runnable() {
                                    @Override
                                    public void run() {
                                            dynamicTimeProperty.set(timeSdf.format(new Date()));
                                            dynamicDateProperty.set(dateSdf.format(new Date()));
                                            progress = progress + 0.01;
                                            progressBar.setProgress(progress);
                                    }
                            });
                            try {
                                    Thread.sleep(100);
                            } catch (InterruptedException ex) {
                                    break;
                            }
                    }
            }
        });
        t.setName("Runnable Time Updater");
        t.setDaemon(true);
        t.start();      
    }      
    
    public void setApp(Main application){
        this.application = application;
    }
}
