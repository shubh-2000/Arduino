#include <SoftwareSerial.h>
#include <dht.h>
#define DHT11_PIN A3//dhtsensor

SoftwareSerial BTSerial(10, 11); // RX | TX
dht DHT;

int sensor_pin = A2;//moisture sensor
int moist ;
boolean chk;
int humid = 0;
int temp = 0;
const int analogInPin = A0; //phsensor
int sensorValue = 7; 
unsigned long int avgValue; 

float b,pHVol,pH;
int buf[10];
int ch;
int i,j,l,c=0;
double avgph=0,avgtemp=0,avgmoist=0;
void setup()
{
  Serial.begin(9600);
  BTSerial.println(F("TEAM G.S.T."));
  BTSerial.begin(9600); 
  
}
void loop() 
{
  
  for(l=0;l<5;l++)
  {
    delay(2000);    
    chk = DHT.read11(DHT11_PIN);
    temp = DHT.temperature;
    humid = DHT.humidity;
    
    avgtemp=avgtemp+temp;
    BTSerial.print("\nTemp:");
    BTSerial.print(temp);
    BTSerial.print(" *C");
    BTSerial.print("\nHumidity:");
    BTSerial.print(humid);
    BTSerial.print("%\n");
    
    //Moisture_Sensor
    moist= analogRead(sensor_pin);
    moist = map(moist,1000,0,0,100);
    avgmoist=avgmoist+moist;
    BTSerial.print("Mositure : ");
    BTSerial.print(moist);
    BTSerial.println("%");    
    
    //pH_Sensor
    for(i=0;i<10;i++) 
    {
      
      buf[i]=analogRead(analogInPin);
    }
    for(i=0;i<9;i++)
    {
      for(j=i+1;j<10;j++)
      {
         if(buf[i]>buf[j])
         {
             temp=buf[i];
             buf[i]=buf[j];
             buf[j]=temp;
         }
      }
    }
    avgValue=0;
    for(i=2;i<8;i++)
    { 
      avgValue+=buf[i];
    }
    pHVol=(float)avgValue*5.0/1024/6;
    pH = -5.70 * pHVol + 21.34;
    
    avgph=avgph+pH;
    BTSerial.print("pH = ");
    BTSerial.println(pH);

  }
    delay(2000);
    BTSerial.print("\nAvgTemp:");
    BTSerial.print((avgtemp)/5);
    BTSerial.print(" *C");
    BTSerial.print("\nAvgMoisture:");
    BTSerial.print((avgmoist)/5);
    BTSerial.print("%\n");
    BTSerial.print("AvgpH : ");
    BTSerial.print((avgph)/5);
    

    delay(2000);
    BTSerial.println("\n\nSelect Your Soil Type");
    BTSerial.println("1.Alluvial");
    BTSerial.println("2.Loam");
    BTSerial.println("3.Sandy");
    
    while(Serial.available()==0){}
    ch=Serial.parseInt();
    
            
    if(ch==1)
    {
      if(avgph>=7.0 && avgph<=8.0)
      {
        if(moist>=10 && moist <=25)
        {
         if(temp>=20 && temp <=27)
         {                  
            BTSerial.println(" :: Rice :: ");
         }
        }
      }
      else
      {
        BTSerial.println("NO DATA AVALIABLE");
      }
    }
    else if(ch==2)
    {
      if(avgph>=6.0 && avgph<=6.5)
      {
        if(avgmoist>=35 && avgmoist <=45)
        {
          if(avgtemp>=20 && avgtemp <=27)
          {
            BTSerial.println(" :: Wheat :: ");
          }
          else if(avgtemp>=7 && avgtemp <=10)
          {
            BTSerial.println(" :: Sorghum :: ");
          }
          else if(avgtemp>=28 && avgtemp <=32)
          {
            BTSerial.println(" :: Tea :: ");
          }
          else
          {
            BTSerial.println("Tempreture Not Suitable");
          }
        }
        else
        {
          BTSerial.println("Moisture Not Suitable");
        }
      }
      else
      {
        BTSerial.println("pH Not Suitable");
      }
    }
    else if(ch==3)
    {
      if(avgph>=5.5 && avgph<=6.5)
      {
         if(avgmoist>=15 && avgmoist <=25)
         {
            if(avgtemp>=15 && avgtemp <=20)
            {
               BTSerial.println(" :: Jowar :: ");
            }
            else if(avgtemp>=27 && avgtemp <=30)
            {
              BTSerial.println(" :: Bajra :: ");
            }
            else
            {
              BTSerial.println("Tempreture Not Suitable");
            }
         }
         else
         {
           BTSerial.println("Moisture Not Suitable");
         }
      }
      else
      {
        BTSerial.println("pH Not Suitable");
      }
    }
    else
    {
      BTSerial.println("Invalid Soil Type");
    }
      for(;;){}
}
  
    
  
