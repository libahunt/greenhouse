void measureTemp() {
/*fills all temp and RH data variables with measurements from DHT11 sensors*/
  
  /*debug*/DPL("starting measuring temperature");

  /*set variables to "unknown" state*/
  tempIn = 222;
  rhIn = -1;
  tempOut = 222;
  rhOut = -1;
  /*initialize communication*/
  DHT11A.acquire();
  DHT11B.acquire();
  
  /*save results*/
  while (DHT11A.acquiring());
  for (i=0; i<tempReadMaxTries;i++) {
    if (DHT11A.getStatus() == IDDHTLIB_OK) {
     tempIn = int(DHT11A.getCelsius());
     rhIn = int(DHT11A.getHumidity());
     break;
    }
  }
  
  while (DHT11B.acquiring());
  for (i=0; i<tempReadMaxTries;i++) {
    if (DHT11B.getStatus() == IDDHTLIB_OK) {
     tempOut = int(DHT11B.getCelsius());
     rhOut = int(DHT11B.getHumidity());
     break;
    }
  }
  
  /*debug*/DP("tempIn = ");
  /*debug*/DPL(tempIn);
  /*debug*/DP("rhIn = ");
  /*debug*/DPL(rhIn);
  /*debug*/DP("tempOut = ");
  /*debug*/DPL(tempOut);
  /*debug*/DP("rhOut = ");
  /*debug*/DPL(rhOut);
  

}


/*needed for library to work*/
void dht11_wrIn() {
  DHT11A.isrCallback();
}
void dht11_wrOut() {
  DHT11B.isrCallback();
}
