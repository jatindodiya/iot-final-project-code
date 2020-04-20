#include <WiFi.h>
#include <FirebaseESP32.h>
#include <Keypad.h>
#include <LiquidCrystal.h>

#define FIREBASE_HOST "parking-tech-88362.firebaseio.com"
#define FIREBASE_AUTH "YxEJ1FoylOOimZsjfwSBEFiJe3QXaPx46nDli1qQ"
#define WIFI_SSID "Ghanshyam1"
#define WIFI_PASSWORD "ghanuiloveu1"
  
FirebaseData firebaseData;

//=======================================================Keypad decleration ===================================
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] =  {
                            {'*','0','#','D'},
                            {'7','8','9','c'},
                            {'4','5','6','B'},
                            {'1','2','3','A'}
                         };
byte rowPins[ROWS] = {32,33,25,26}; 
byte colPins[COLS] = {27,14,12,13};
Keypad mykeypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );
//====================================================================================================================

int ir[6] = {39,34,36,15,22,23}; // IR sensor pins

const int rs = 21, en = 19, d4 = 18, d5 = 5, d6 = 17, d7 = 16;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//================================================================================================================

int serial,temp,trial,slotnumber,uid,otp;

//=======================================================================================================
void parkingdataupload()
{

   Firebase.setString(firebaseData, "/message", "parking data upload");
   delay(1000);
   if(digitalRead(ir[0]) == 1){
        Firebase.setInt(firebaseData, "/p1", 1);
      }else{
        Firebase.setInt(firebaseData, "/p1", 0);
      }
      
      if(digitalRead(ir[1]) == 1)
      {
        Firebase.setInt(firebaseData, "/p2", 1);
      }else{
        Firebase.setInt(firebaseData, "/p2", 0);  
      }
   
      if(digitalRead(ir[2]) == 1)
      {
        Firebase.setInt(firebaseData, "/p3", 1);
      }else{
        Firebase.setInt(firebaseData, "/p3", 0);
      }
      
       if(digitalRead(ir[3]) == 1)
      {
        Firebase.setInt(firebaseData, "/p4", 1);
       }else{
        Firebase.setInt(firebaseData, "/p4", 0);
      }
      
      if(digitalRead(ir[4]) == 1)
      {
        Firebase.setInt(firebaseData, "/p5", 1);
      }else{
        Firebase.setInt(firebaseData, "/p5", 0);
      }

      if(digitalRead(ir[5]) == 1){
        Firebase.setInt(firebaseData, "/p6", 1);
      }else{
        Firebase.setInt(firebaseData, "/p6", 0); 
      }
      
      Firebase.setString(firebaseData, "/message", "Exit parking data upload");
      delay(1000);
}
//==================================================================================================

//void parkingdatauploadexit()
//{
//
//   Firebase.setString(firebaseData, "/message", "exit gate upload");
//   delay(1000);
//   if(digitalRead(ir[0]) == 1){
//        Firebase.setInt(firebaseData, "/p1", 1);
//      }else{
//        Firebase.setInt(firebaseData, "/p1", 0);
//      }
//      
//      if(digitalRead(ir[1]) == 1)
//      {
//        Firebase.setInt(firebaseData, "/p2", 1);
//      }else{
//        Firebase.setInt(firebaseData, "/p2", 0);  
//      }
//   
//      if(digitalRead(ir[2]) == 1)
//      {
//        Firebase.setInt(firebaseData, "/p3", 1);
//      }else{
//        Firebase.setInt(firebaseData, "/p3", 0);
//      }
//      
//       if(digitalRead(ir[3]) == 1)
//      {
//        Firebase.setInt(firebaseData, "/p4", 1);
//       }else{
//        Firebase.setInt(firebaseData, "/p4", 0);
//      }
//      
//      if(digitalRead(ir[4]) == 1)
//      {
//        Firebase.setInt(firebaseData, "/p5", 1);
//      }else{
//        Firebase.setInt(firebaseData, "/p5", 0);
//      }
//
//      if(digitalRead(ir[5]) == 1){
//        Firebase.setInt(firebaseData, "/p6", 1);
//      }else{
//        Firebase.setInt(firebaseData, "/p6", 0); 
//      }
//      
//      Firebase.setString(firebaseData, "/message", "Exit parking data upload");
//      delay(1000);
//}

//============================================================================================
void uidfromuser()
{ 
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter User ID");
  Firebase.setString(firebaseData, "/message", "uid from user");
  delay(1000);
  trial++;
  temp = 0;
  uid = 0;
  lcd.setCursor(0, 1);    
  while(temp != 3)
  {
    char keypressed = mykeypad.getKey();
    if (keypressed != NO_KEY)
      {
        lcd.print(keypressed);
          if(temp == 0)
          {
            uid = uid + (100*int(keypressed-'0'));
          }
          else if(temp == 1)
          {
            uid = uid + (10*int(keypressed-'0'));
          }
          else if(temp == 2)
          {
            uid = uid + int(keypressed-'0');
          }
        temp = temp+1;
      }
   } 
}
//============================================================================================
void checkuid()
{
  Firebase.setString(firebaseData, "/message", "check uid ");
  delay(3000);
  slotnumber =0;
         int tempuid1 = Firebase.getInt(firebaseData, "/uid1");
         tempuid1 = firebaseData.intData();
         if(uid == tempuid1){
                slotnumber = 1;
                Firebase.setString(firebaseData, "/message", "slot number 1");
                lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("slotnumber");
                lcd.setCursor(0, 1);
                lcd.print(" is 1");
                delay(3000);
         }
         int tempuid2 = Firebase.getInt(firebaseData, "/uid2");
         tempuid2 = firebaseData.intData();
         if(uid == tempuid2){
                 slotnumber = 2;
                 Firebase.setString(firebaseData, "/message", "slot number 2");
                 lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("slotnumber");
                lcd.setCursor(0, 1);
                lcd.print(" is 2");
                delay(3000);
         }
         int tempuid3 = Firebase.getInt(firebaseData, "/uid3");
         tempuid3 = firebaseData.intData();
         if(uid == tempuid3){
                   slotnumber = 3;
                   Firebase.setString(firebaseData, "/message", "slot number 3");
                   lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("slotnumber");
                lcd.setCursor(0, 1);
                lcd.print(" is 3");
                delay(3000);
         }
         int tempuid4 = Firebase.getInt(firebaseData, "/uid4");
         tempuid4 = firebaseData.intData();
         if(uid == tempuid4){
                    slotnumber = 4;
                    Firebase.setString(firebaseData, "/message", "slot number 4");
                    lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("slotnumber");
                lcd.setCursor(0, 1);
                lcd.print(" is 4");
                delay(3000);
         }
         int tempuid5 = Firebase.getInt(firebaseData, "/uid5");
         tempuid5 = firebaseData.intData();
         if(uid == tempuid5){
                  slotnumber = 5;
                  Firebase.setString(firebaseData, "/message", "slot number 5");
                  lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("slotnumber");
                lcd.setCursor(0, 1);
                lcd.print(" is 5");
                delay(3000);
         }
         int tempuid6 = Firebase.getInt(firebaseData, "/uid6");
         tempuid6 = firebaseData.intData();
         if(uid == tempuid6){
                  slotnumber = 6;
                  Firebase.setString(firebaseData, "/message", "slot number 6");
                  lcd.clear();
                lcd.setCursor(0, 0);
                lcd.print("slotnumber");
                lcd.setCursor(0, 1);
                lcd.print(" is 6");
                delay(3000);
         }
         if((slotnumber == 0) && (trial <3))
         {
            lcd.print(" Wrong UserID");
            Firebase.setString(firebaseData, "/message", "Wrong uid");
            delay(3000);
            uidfromuser();  
         }

         if((trial < 3) && (slotnumber > 0) && (slotnumber < 7)){
              
               otpfromuser();
           }
}
//=============================================================================================================

void otpfromuser()
{ 
  Firebase.setString(firebaseData, "/message", "otp from user");
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Enter OTP");
  temp = 0;
  otp = 0;
  lcd.setCursor(0, 1);
       
  while(temp != 4)
  {
    char keypressed = mykeypad.getKey();
    if (keypressed != NO_KEY)
      {
      lcd.print(keypressed);
          if(temp == 0)
          {
            otp = otp + (1000*int(keypressed-'0'));
          }
          else if(temp == 1)
          {
            otp = otp + (100*int(keypressed-'0'));
          }else if(temp == 2)
          {
            otp = otp + (10*int(keypressed-'0'));
          }
          else if(temp == 3)
          {
            otp = otp + int(keypressed-'0');
          }  
      temp = temp+1;
      }
  }
  
  checkotp();
}

//====================================================================================================

void checkotp()
{
  Firebase.setString(firebaseData, "/message", "check otp");
  delay(2000);
  switch (slotnumber) {
  
    case 1:
    {
       int otp1 = Firebase.getInt(firebaseData, "/otp1");
       otp1 = firebaseData.intData();
       if(otp == otp1)
       {
          Firebase.setString(firebaseData, "/message", "sending slot number 1");
            
            Serial.print("1");
       }
      break;
    }
    case 2: 
    {
       int otp2 = Firebase.getInt(firebaseData, "/otp2");
       otp2 = firebaseData.intData();
       if(otp == otp2)
       {
          Firebase.setString(firebaseData, "/message", "sending slot number 2");
          
            Serial.print("2");
       }
      break;
    }
    case 3: 
    {
       int otp3 = Firebase.getInt(firebaseData, "/otp3");
       otp3 = firebaseData.intData();
       if(otp == otp3)
       {
      
          Firebase.setString(firebaseData, "/message", "sending slot number 3");
          
            Serial.print("3");
       }
      break;
    }
    case 4: 
    {
       int otp4 = Firebase.getInt(firebaseData, "/otp4");
       otp4 = firebaseData.intData();
       if(otp == otp4)
       {
          Firebase.setString(firebaseData, "/message", "sending slot number 4");
          
            Serial.print("4");
       }
      break;
    }
    case 5: 
    {
       int otp5 = Firebase.getInt(firebaseData, "/otp5");
       otp5 = firebaseData.intData();
       if(otp == otp5)
       {
     
          Firebase.setString(firebaseData, "/message", "sending slot number 5");
          
            Serial.print("5");
          
       }
      break;
    }
    case 6: 
    {
       int otp6 = Firebase.getInt(firebaseData, "/otp6");
       otp6 = firebaseData.intData();
       if(otp == otp6)
       {
      
         Firebase.setString(firebaseData, "/message", "sending slot number 6");
         
            Serial.print("6");
       }
      break;
    }
  }
            lcd.clear();
            lcd.setCursor(0, 0);
            lcd.print("Follow The LED");
            lcd.setCursor(0, 1);
            lcd.print("Indicator");
  //i can send data from here and wait till i get data back
  delay(10000);
}

//============================================================================================================================
void setup()                                                              //   ----------set up-----------
{
    for(int i=0; i<6;i++)
    {
        pinMode(ir[i],INPUT);
    }
    Serial.begin(115200);
    
    lcd.begin(16, 2);

    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                  
    while (WiFi.status() != WL_CONNECTED){  
        delay(300);
        }
   
    delay(2000);
    Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
    Firebase.reconnectWiFi(true);                                //auto connect wifi if connection lost
                                                             
    Firebase.setString(firebaseData, "/message", "im in setup");
    parkingdataupload();
}

//==========================================================================================================

void loop()
{
  if(Serial.available() > 0)                      // this will check weather serial monitor has any input ot not 
   {
      Firebase.setString(firebaseData, "/message", "in loop checking for input");
      char serialc = Serial.read();
      serial = int(serialc-'0');
      if(serial == 0)
      {   
          char serialc = Serial.read();
          serial = int(serialc-'0');
          Firebase.setString(firebaseData, "/message", "im in entry gate");
          
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("welcom To");
          lcd.setCursor(0, 1);
          lcd.print("Stark Parking");
          delay(5000);
          trial = 0;
          uidfromuser();
          checkuid();
          delay(5000);
          
      }
      else if(serial == 1)
      {
        char serialc = Serial.read();
        serial = int(serialc-'0');
        Firebase.setString(firebaseData, "/message", "im in exit gate");
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Thank You");
        lcd.setCursor(0, 1);
        lcd.print("Visit Again");
        parkingdataupload();
        
        delay(5000);
      }
   }
   else{
    lcd.clear();
    Firebase.setString(firebaseData, "/message", "im outside ");
   }
}
