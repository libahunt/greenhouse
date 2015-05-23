void logData() { 
  
  if (!sd.begin(sdCS, SPI_HALF_SPEED)) {//no SD card
    /*debug*/DPL("SD card not present");
    return; //quit trying to log
  }

  if (!file.open("datalog.txt", O_CREAT | O_APPEND | O_WRITE )) {
    /*debug*/DPL("SD file error");
    return;//quit trying to log
  }
  
  /*debug*/DPL("SD file ok");
  file.print(tempOut, DEC);
  file.print(",");
  file.print(rhOut, DEC);
  file.print(",");
  file.print(tempIn, DEC);
  file.print(",");
  file.print(rhIn, DEC);
  file.print(",");
  file.print(anemoMaxRpm, DEC);
  file.print(",");
  file.println(newState, DEC);
  file.close();
  /*debug*/DPL("log done");

} // logData()


void logReset() {
  
  if (!sd.begin(sdCS, SPI_HALF_SPEED)) {//no SD card
    /*debug*/DPL("SD card not present");
    return; //quit trying to log
  }
  if (!file.open("datalog.txt", O_CREAT | O_APPEND | O_WRITE )) {
    /*debug*/DPL("SD file error");
    return; //quit trying to log
  }
  
  /*debug*/DPL(((float) interval) / 60);
  /*debug*/DPL("SD file ok");
  file.println("Temperature outside (deg C),Relative humidity outside(%),Temperature inside (deg C),Relative humidity inside(%),Anemometer RPM,State (0-closed 1-open)");
  file.print("Interval is ");
  file.print( ((float) interval) / 60 );
  file.print("minutes");
  /*debug*/#ifdef DEBUG
  /*debug*/  file.print(". Debug is ON");
  /*debug*/#endif
  file.println(".");
  file.close();
  /*debug*/DPL("log reset done");
 
} // logReset() 
