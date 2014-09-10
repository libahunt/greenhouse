/*************************************************************************************
Serial debugging function
based on http://forum.arduino.cc/index.php?PHPSESSID=t751ftglgpibikp8fa2h70o8s4&topic=46900.msg338653#msg338653 
*************************************************************************************/

#ifdef DEBUG
  #define DP(str) \
    Serial.print(str); \
    Serial.print(" ");
   #define DPL(str) \
    Serial.println(str);
#else
  #define DP(str)
  #define DPL(str)
#endif

/*#ifdef DEBUG
  #define DP(str) \
    Serial.print(millis()); \
    Serial.print(": "); \
    Serial.print(__PRETTY_FUNCTION__); \
    Serial.print(" "); \
    Serial.print(str);
   #define DPL(str) \
    //Serial.print(millis()); \
    Serial.print(": "); \
    Serial.print(__PRETTY_FUNCTION__); \
    Serial.print(" "); \
    Serial.println(str);
#else
  #define DP(str)
  #define DPL(str)
#endif*/
