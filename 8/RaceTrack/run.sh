#!/bin/bash
javac --module-path $PATH_TO_FX --add-modules=javafx.controls,javafx.fxml RaceTrack.java
java --module-path $PATH_TO_FX --add-modules javafx.controls RaceTrack