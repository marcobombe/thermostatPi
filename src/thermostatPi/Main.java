/*
 * Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
 */
package thermostatPi;

import java.io.InputStream;
import java.util.logging.Level;
import java.util.logging.Logger;
import javafx.application.Application;
import javafx.fxml.FXMLLoader;
import javafx.fxml.Initializable;
import javafx.fxml.JavaFXBuilderFactory;
import javafx.scene.Scene;
import javafx.scene.layout.AnchorPane;
import javafx.stage.Stage;
import thermostatPi.model.User;
import demo.security.Authenticator;
import java.util.Locale;
import java.util.ResourceBundle;
import thermostatPi.model.GLOBALS;

/**
 * Main Application. This class handles navigation and user session.
 */
public class Main extends Application {

    private Stage stage;
    private User loggedUser;


    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        Application.launch(Main.class, (java.lang.String[])null);
    }

    @Override
    public void start(Stage primaryStage) {
        try {
            stage = primaryStage;
            stage.setTitle(GLOBALS.appName);
            stage.setWidth(GLOBALS.MINIMUM_WINDOW_WIDTH);
            stage.setHeight(GLOBALS.MINIMUM_WINDOW_HEIGHT);
            stage.setResizable(false);
            gotoLogin();
            primaryStage.show();
        } catch (Exception ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    public User getLoggedUser() {
        return loggedUser;
    }
        
    public boolean userLogging(String userId, String password){
        if (Authenticator.validate(userId, password)) {
            loggedUser = User.of(userId);
            gotoProfile();
            return true;
        } else {
            return false;
        }
    }
    
    void userLogout(){
        loggedUser = null;
        gotoLogin();
    }
    
    public void gotoProfile() {
        try {
            ProfileController profile = (ProfileController) replaceSceneContent("profile.fxml");
            profile.setApp(this);
        } catch (Exception ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }
    
    public void gotoSettings() {
        try {
            SettingsController settings = (SettingsController) replaceSceneContent("settings.fxml");
            settings.setApp(this);
        } catch (Exception ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private void gotoLogin() {
        try {
            LoginController login = (LoginController) replaceSceneContent("login.fxml");
            login.setApp(this);
        } catch (Exception ex) {
            Logger.getLogger(Main.class.getName()).log(Level.SEVERE, null, ex);
        }
    }

    private Initializable replaceSceneContent(String fxml) throws Exception {
        Locale locale = new Locale("it", "IT");
        FXMLLoader loader = new FXMLLoader();
        loader.setResources(ResourceBundle.getBundle("bundles.lang_it", locale));
        InputStream in = Main.class.getResourceAsStream(fxml);
        loader.setBuilderFactory(new JavaFXBuilderFactory());
        loader.setLocation(Main.class.getResource(fxml));
        AnchorPane page;
        try {
            page = (AnchorPane) loader.load(in);
        } finally {
            in.close();
        } 
        Scene scene = new Scene(page, 480, 320);
        stage.setScene(scene);
        stage.sizeToScene();
        return (Initializable) loader.getController();
    }
}
