
#include <dht11.h>
#define DHT11PIN 3 //The pin that DHT11 is connected to the Arduino
int ldr= A0;//The pin that ldr is connected to the Arduino
dht11 DHT11;//variable of type dht11
int VarTime;//Variable used in seconds measurement
int delayTime=3000;
int monthDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};//Variable that holds how many days a month lasts
int hour=18;//hour variable
int minute=40;//minute variable
int second=55;//second variable
int day=2;//day variable
int month =6;//month variable
int year =2021; //year variable
bool dayFlag=false;//Variable that is true to increase by 1 day when 24 hours are up
void setup() {//Setup Function
  Serial.begin(9600);//To initiate serial communication
  VarTime= millis();//The part where the time is taken first with the millis() function

}
void time(){//function for calculating time and date
  if((millis()-VarTime)>1000){
    second=second+1;//every second the second variable increases by 1
    if(second>=60){//If the second is greater than or equal to 60, the mode is changed to 60 and the minute variable is increased by 1.
      second=second%60;
      minute =minute +1;
      if(minute>=60){//If minutes is greater than or equal to 60, the minute variable becomes 0 and the hour variable is incremented by 1.
        minute=0;
        hour =hour+1;
        if(hour>=24){//If the hour variable exceeds 24 , the hour variable becomes 0 and the dayFlag becomes true , the day increases
          hour=0;
          dayFlag=true;
        }
      }
    }

    if(dayFlag){//If dayFlag is true then the day variable is incremented by 1.
      day=day+1;
      if( month==2 ){//February has 29 days every 4 years. Therefore, February is controlled differently.
        if(year%4==0 && day>29){
        day=1;
        month=month+1;
        }
        else if(day >28){
                  day=1;
        month=month+1;
        }

      }
      else if(day>monthDays[month-1]){// Whether the 1 month is over or not is checked by the monthDays array.
        day=1;//If the month is over, the day variable becomes 1 and the month increases by 1
        month=month+1;
      }
      
      if(month>12){//If the month is over, the day variable becomes 1 and the month increases by 1
        month=1;
        year=year+1;
      }
    }
    dayFlag=false;//dayFlag variable stays false until 24 hours
  
    VarTime=millis();// the part where the time is retrieved with the millis() function
  }
    Serial.print("Date:");//Displaying date on serial port screen
    if(day<10){//If day is a number less than 10, '0' is added to the beginning.
      Serial.print("0");
      Serial.print(day);
    }
    else{//If the day is greater than 10, it will be displayed directly on the screen.
      Serial.print(day);
    }
    Serial.print(".");
    if(month<10){//If month is a number less than 10, '0' is added to the beginning.
      Serial.print("0");
      Serial.print(month);
    }
    else{//If the month is greater than 10, it will be displayed directly on the screen.
      Serial.print(month);
    }
    Serial.print(".");
    Serial.print(year);//display of the year
    Serial.print(" - ");
    
    Serial.print("Hour:");//Displaying hour on serial port screen
    if(hour<10){//If hour is a number less than 10, '0' is added to the beginning.
      Serial.print("0");
      Serial.print(hour);
    }
    else{//If the hour is greater than 10, it will be displayed directly on the screen.
      Serial.print(hour);
    }
    Serial.print(":");
    if(minute<10){//If minute is a number less than 10, '0' is added to the beginning.
      Serial.print("0");
      Serial.print(minute);
    }
    else{//If the minute is greater than 10, it will be displayed directly on the screen.
      Serial.print(minute);
    }
    Serial.print(":");
    if(second<10){//If second is a number less than 10, '0' is added to the beginning.
      Serial.print("0");
      Serial.print(second);
    }
    else{//If the second is greater than 10, it will be displayed directly on the screen.
      Serial.print(second);
    }
  
  
}


void loop() {// loop function
  

  time();//The part where the time function is called
  second=second+((delayTime/1000)-1);//The seconds are increased by the expected time due to the delay time
  int ldrValue =analogRead(ldr);//the part where the value is read from ldr
  int dht11Read =DHT11.read(DHT11PIN);//the part where the value is read from dht11
  Serial.print(" - Light :");
  Serial.print(ldrValue);//It is the part where the light measured with ldr is printed on the screen.
  
  Serial.print(" - Temperature :");
  Serial.print((float)DHT11.temperature , 2 );//It is the part where the temperature measured with dht11 is printed on the screen.
  Serial.print("°C");
  
  Serial.print(" - Humidity (%):");
  Serial.print((float)DHT11.humidity , 2 );//It is the part where the humidity measured with dht11 is printed on the screen.
  Serial.print("%");
  Serial.println();

 //Light
 if(ldrValue>=400){//If the value read from ldr is greater than 400, it is the day.
  Serial.print("Day");
 }
 else{//If the value read from ldr is less than 400, it is the night.
  Serial.print("Night");
 }
 //temperature
  if((float)DHT11.temperature>=20 &&(int)DHT11.temperature<=24 &&ldrValue>=400){//'Optimal Temperature' if it is a day and the temperature is between 20-24 °C.
    Serial.print(" - Optimal Temperature");
  }
  else if((float)DHT11.temperature<20 && ldrValue>=400 ){//'Cold' if it is a day and the temperature is less than 20°C.
    Serial.print(" - Cold");
  }
  else if ((float)DHT11.temperature>24 && ldrValue>=400){//'Hot' if it is a day and the temperature is greater than 20°C.
    Serial.print(" - Hot");
  }
  else if((float)DHT11.temperature>=18 &&(float)DHT11.temperature<=21 &&ldrValue<400){//'Optimal Temperature' if it is a night and the temperature is between 18-21 °C.
    Serial.print(" - Optimal Temperaure");
  }
  else if((float)DHT11.temperature<18 && ldrValue<400 ){//'Cold' if it is a night and the temperature is less than 18°C.
    Serial.print(" - Cold");
  }
  else if ((float)DHT11.temperature>21 && ldrValue<400){//'Hot' if it is a night and the temperature is greater than 21°C.
    Serial.print(" - Hot");
  }
  //Humidity
  if((float)DHT11.humidity >=30 &&(float)DHT11.humidity <=50){//'Optimal Humidity' if humidity is between 30-50.
    Serial.print(" - Optimal Humidity");
  }
  else if((float)DHT11.humidity <30){//'Low Humidity' if humidity is less than 30.
    Serial.print(" - Low Humidity");
  }
  else if((float)DHT11.humidity >50){
    Serial.print(" - High Humidity");//'High Humidity' if humidity is greater than 50.
  }
  Serial.println();
  Serial.println();
  delay(delayTime);

}
